import curses
from typing import Any, Callable, List, Optional, Type


class Question:
    def __init__(
        self,
        question: str,
        response_type: Optional[type] = str,
        options: Optional[List[str]] = None,
        default: Any = None,
        validator: Optional[Callable[[Any], bool]] = None,
        help_text: Optional[str] = None,
    ):
        self.question = question
        self.response_type = response_type or str
        self.options = options
        self.default = default
        self.validator = validator
        self.help_text = help_text

    def _select_option(self, stdscr):
        if not self.options:
            raise ValueError
        curses.curs_set(0)
        current_selection = 0

        while True:
            stdscr.clear()
            stdscr.addstr(f"{self.question}\n\n")
            for idx, option in enumerate(self.options):
                if idx == current_selection:
                    stdscr.addstr(f"> {option}\n", curses.A_REVERSE)
                else:
                    stdscr.addstr(f"  {option}\n")
            stdscr.refresh()

            key = stdscr.getch()
            if key == curses.KEY_UP and current_selection > 0:
                current_selection -= 1
            elif key == curses.KEY_DOWN and current_selection < len(self.options) - 1:
                current_selection += 1
            elif key in (curses.KEY_ENTER, 10, 13):  # Enter key
                return self.options[current_selection]

    def ask(self):
        if self.options:
            return curses.wrapper(self._select_option)

        while True:
            try:
                prompt = f"{self.question} "
                if self.default is not None:
                    prompt += f"[Default: {self.default}] "

                response = input(prompt) or self.default

                if response is None:
                    print("This question requires a response.")
                    continue

                response = self.response_type(response)

                if self.validator and not self.validator(response):
                    print("Invalid response. Please try again.")
                    continue

                return response

            except ValueError:
                print(f"Invalid input. Please enter a valid {self.response_type.__name__}.")


class Quiz:
    def __init__(self):
        self.questions: List[Question] = []

    def question(self, q: Type):
        question_text = getattr(q, "question", None)
        response_type = getattr(q, "response_type", str)
        options = getattr(q, "options", None)
        default = getattr(q, "default", None)
        validator = getattr(q, "validator", None)
        help_text = getattr(q, "help_text", None)

        if not question_text:
            raise ValueError(f"The class {q.__name__} must define a 'question' attribute.")

        question = Question(
            question=question_text,
            response_type=response_type,
            options=options,
            default=default,
            validator=validator,
            help_text=help_text,
        )
        self.questions.append(question)
        return question

    def run(self):
        responses = {}
        for question in self.questions:
            print()
            if question.help_text:
                print(f"Help: {question.help_text}")
            responses[question.question] = question.ask()
        return responses

    def reorder_questions(self, order: List[int]):
        """Reordena as perguntas com base em uma lista de índices."""
        self.questions = [self.questions[i] for i in order]


# Definir perguntas como classes decoradas
app = Quiz()

@app.question
class Q1:
    question = "What is your name?"
    response_type = str
    help_text = "Enter your full name."

@app.question
class Q2:
    question = "Your age?"
    response_type = int
    validator = lambda x: x > 0
    help_text = "Age must be a positive number."

@app.question
class Q3:
    question = "Are you m or w?"
    options = ["m", "w"]
    default = "m"
    help_text = "Enter 'm' for male or 'w' for female. Default is 'm'."

@app.question
class Q4:
    question = "Do you like Python?"
    options = ["yes", "no"]
    default = "yes"
    help_text = "Just be honest :)"


responses = app.run()

print("\nYour responses:")
print(responses)
