# Instructions

Update this document where indicated look for the brackets! Replace text inside the brackets with your own information. For example: Course Name should be the name of this course, and not the generic words "Course Name".

<br>

# Project and Portfolio I: Computer Science - Online

- Spiegel, Thomas
- 11/01/2026

This paper addresses some of the topic matter covered in research and activity this week. Be sure to include reference links below to the research and information you used to complete this assignment.

## Topic: Terminal

Professional developers use Terminal daily. It's essential to understand some fundamental commands to use the application.

Update the information below to demonstrate your knowledge on this topic.

**1. Using Terminal, there are essential commands to know.**

List the correct Terminal commands to do the actions listed below. Replace **CMD** with the correct command sequence. You can keep or enhance the brief description.

**The last bullet provides an example**.

- `clear`: Clear the Screen
- `pwd`: Print the "Working Directory"
- `ls`: List files and folders
- `ls -a`: List files and folders, including invisible files
- `ls -lah`: List all files and folders, in human readable form
- `cd folderName`: Change directory
- `cd /`: Change directory, go to root directory
- `cd ~`: Change directory and go to user home directory
- `cd ..`: Change directory, go up one folder level
- `cd ../..`: Change directory, go up two folder levels
- `cd ~/Desktop`: Change directory to my desktop!

**2. Using Terminal...**

**Folder Drop:** Try typing "cd" followed by a space, and then drag a folder into terminal and press return. Test this out and describe your results below.

When I typed "cd " and dragged my Minesweeper Project folder into the terminal, it automatically pasted the folder's full path (in quotes, because the folder name has a space). After pressing Enter, the terminal moved into that folder, and running `pwd` confirmed I was inside it. This is a fast way to navigate to a folder without typing out a long path.

## Topic: Version Control & Git

Version control, also known as revision control, records changes to a file or set of files over time so that you can recall specific versions later. In this class, we are learning Git. Update the information below where indicated.

**1. There are three types of version control.**

**Local Version Control:** Saving copies of files in different folders or with new version numbers on your own computer. It's simple, but it's easy to overwrite the wrong file or lose track of which version is current. 

**Centralized Version Control (CVCS):** One shared server stores the project and its history, and developers check out the files they need. Everyone can see who is working on what, and administrators control access, but if the server goes down nobody can work, and if it crashes without backups the history is lost. Examples: CVS, Subversion, Perforce. 

**Distributed Version Control (DVCS):** Every developer has a full copy of the repository, including its entire history, on their own computer. If the server fails, any copy can restore it, and developers can work offline and with multiple remote repositories. Examples: Git, Mercurial, Bazaar, Darcs.

**2. Using Terminal, there are also essential Git commands to know.**

List the correct Git commands to do the actions listed below in Terminal. Replace CMD with the correct command and keep or enhance the brief description.

- `git clone <repo-url>`: Clone a repository
- `git config --global user.name "Thomas Spiegel"`: Set-up a global user name
- `git config --global user.email "your-email@example.com"`: Set-up a global email address (to match my GitHub account email)
- `git status`: Shows the current state of your directory and staging area
- `git add .`: Add modified files to the next commit
- `git commit -m "Your message here"`: Make a commit with a new message
- `git log`: Show my commit history
- `git help` : Show Git's help screen

**3. Connecting to GitHub using Terminal.**
HTTPS is the the correct way to connect to GitHub in this course. Describe how you connect to GitHub from Terminal using this protocol. What steps do you take?

1. On GitHub, open the repository, click the green **Code** button, choose **HTTPS**, and copy the URL (for example, https://github.com/trspiegel/Minesweeper-Project.git). 2. In Terminal, use `cd` to go to the folder where I want the project. 3. Run `git clone <repo-url>` to download the repository, then `cd` into it. 4. The first time I push or pull, Git asks me to sign in to GitHub. On Windows, Git Credential Manager opens a browser to log in. GitHub no longer accepts account passwords in the terminal, so a personal access token is used instead if prompted. 5. To connect a project that already exists on my computer, I run `git remote add origin <repo-url>`, then `git push -u origin main`. 6. I check the connection with `git remote -v`, which lists the repository's fetch and push URLs.

**4. Using .gitignore and Why it's Important**  
Most repositories contain a .gitignore file.

- What is the purpose of this file?
A .gitignore file tells Git which files and folders it should not track. It keeps things like build output, editor settings, and system files out of the repository, so the repo stays clean and small and only contains the files that actually make up the project.

- What is the "**.DS_Store**" file and why would you want to ignore it?
.DS_Store is a hidden file that macOS Finder creates in every folder to save view settings like icon positions and sort order. It isn't part of the project, it changes constantly, and it would add clutter and possible merge conflicts to every commit, so it should be ignored. (Windows creates similar files like Thumbs.db and desktop.ini.)

- What other file or folder would you want to add to a .gitignore file and why?
For my Visual Studio C++ project, I would ignore the `.vs/` folder and the `x64/` (or `Debug/` and `Release/`) build folders. `.vs/` holds Visual Studio's cache and my personal settings, and the build folders hold compiled files like .exe and .obj that are recreated every time I build. They're large, specific to my computer, and anyone can generate them from the source code, so they don't belong in the repository.

# Reference Links

Replace the example references below with your own links and recommended resources. It is acceptable to provide multiple links for a single topic and to use material provided to you in this class. You are encouraged to link to your own independent research as well.

The most helpful resource this past week was the Git Commands PDF from class, because it puts the commands I use most in one place. I also learned a lot from troubleshooting my own repository: after I renamed my branch from master to main, every push recreated master on GitHub. Fixing it taught me how a local branch tracks a remote branch, and I solved it with `git fetch --prune` and `git branch -u origin/main main`.

**Terminal Commands** 
Command Line Basics for Beginners (freeCodeCamp) https://www.freecodecamp.org/news/command-line-basics-for-beginners

**Three Types of Version Control**  
Pro Git: About Version Control (https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control)

**Git Commands**  
GitHub Docs: Git Cheatsheet (https://docs.github.com/en/get-started/git-basics/git-cheatsheet)

**Connecting to GitHub using Terminal**  
GitHub Docs: Cloning a Repository (https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)

**Using .gitignore and Why it's Important**  
GitHub Docs: Ignoring Files (https://docs.github.com/en/get-started/git-basics/ignoring-files)
