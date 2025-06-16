🎮 Quiz Console Application
A C++ console-based quiz platform allowing players to solve quizzes, track progress, and interact with various types of questions. Includes an admin panel for moderation and content management.

✨ Features
👤 User System
signup – Register a new player account.

login / logout – User authentication system.

view-profile – Displays personal information and statistics.

view-messages – View messages sent to your account.

🧠 Quiz System
create-quiz – Players can create a quiz.

add-question – Add questions of various types:

True/False

Single Choice

Multiple Choice

Short Answer

Matching Pairs

play-quiz – Solve a quiz in NORMAL or TEST mode, with optional question shuffling.

view-quizzes – Lists all available quizzes.

show-favorites / remove-favorite – Manage favorite quizzes.

🏆 Player Progress & Challenges
Players earn points for solving quizzes.

view-challenges – View active challenge progress.

progress-challenge – Manually trigger progress for a challenge.

🛠 Admin Panel (admin-panel)
Accessible only by administrators:

view-users – View all users.

approve-quiz – Approve quizzes created by players.

Ban – Ban specific users.

view-quizzes – See all published quizzes.

remove-quiz – Remove quizzes from the system.

quiz-stats – View statistics about quizzes.

reset-progress – Reset a player's progress.

🗂 File Structure
Vector.hpp – Custom dynamic array implementation.

Users.h / Player.h / Admin.h – User class hierarchy.

Quiz.h and question types – Abstract base quiz class and its polymorphic children.

UsersFactory / QuestionFactory – Factory patterns for dynamic object creation.

Utils.h – Utility functions.

users.txt – Text file for persisting user data.

🚀 How to Run
Compile with a C++ compiler supporting C++11 or newer.

Run the executable.

Use the CLI interface to interact (type help to see all commands).

🧪 Sample Commands
markdown
Копиране
Редактиране
> signup
> login
> create-quiz
> add-question
> play-quiz
> view-challenges
> admin-panel
🔒 Roles
Role	Description
Player	Can create quizzes, play them, and view progress
Admin	Has access to moderation tools and user/quiz management

📌 Notes
Quizzes must be approved by an admin before they can be played by other users.

Quiz scoring and challenge tracking are only available in player mode.
