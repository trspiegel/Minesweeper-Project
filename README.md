

<br>

# Project & Portfolio 1



Hello my name is Thomas. I am a student from Saint Louis. The purpose of this repository is to practice development using version control. This work will help me begin to build a portfolio of skills and accomplishment that can be shared in the future.

<br>

## 📢 &nbsp; Weekly Stand Up

Each week I will summarize my milestone activity and progress by writing a stand-up. A stand-up is meant to be a succinct update on how things are going. Use these prompts as a guide on what to write about:

⚙️ Overview - What I worked on this past week
<br>
🌵 Challenges - What problems did I have & how I'm addressing them
<br>
🏆 Accomplishments - What is something I "leveled up" on this week
<br>
🔮 Next Steps - What I plan to prioritize and do next

<br>

### Week 1

*Overview:** This week I chose my project, a console Minesweeper game in C++, and built its foundation. I set up a private GitHub repo with `main` and `dev` branches, organized the course folder structure, and created a Project board with an Issue for each feature. I built four classes (Cell, Board, Game, and Input) with headers in /dev/include and source files in /dev/src. The program has a main menu, prints a 9 x 9 board stored as a 2D vector with row and column labels, lets the player reveal cells, and rejects bad input without crashing. I also added a testing log and changelog to /docs.

**Challenges:** Git gave me the most trouble. After renaming `master` to `main`, every push recreated `master` because my local branch was still tracking `origin/master`. I fixed it with `git fetch origin --prune` and `git branch -u origin/main main`. Visual Studio also opened my project in Folder View, so my new class files weren't part of the build until I opened the .slnx file and added them to the project.

**Accomplishments:** I leveled up my understanding of how local branches connect to remote branches, and how the Visual Studio project file controls which files get compiled. I also learned to stage only certain files so each commit covers one piece of work.

**Next Steps:** In Week 2, I'm making the game playable: placing mines randomly with a safe first move, counting nearby mines, auto-revealing empty areas, adding flags, and detecting a win or loss.

### Week 2

My next stand up will go here...

### Week 3

Stay tuned, this stand up is coming soon...

### Week 4

My final stand up...
