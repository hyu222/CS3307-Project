# CS3307_Project

C++ Project for CS3307.

## First Time Using Repository

1) Download Git Bash from https://git-scm.com/downloads

//Create an SSH Key if needed.

2) Type in `git config --global user.name "John Doe"` using your Real Name.

3) Navigate to a folder of your liking to store your code. Ex) `mkdir CodeFolder` then `cd CodeFolder/` to just make a folder and go to it.

4) Use `git clone git@github.com:anthonysg/CS3307_Project.git` to get the project.

5) `cd CS3307_Project/` to go into the project.

6) Use `git pull` to get the latest version of the project.

7) `git status` to check the status, it should say that there is nothing to commit.

### Awesome, now you have the latest version of the project.

## Adding or Modifying the Project

Let's say you want to add a file or modify a file in the repository. 

1) Navigate to the Project folder.

2) Get the latest version of the repository using `git pull`.

3) Create a new Branch using `git checkout -b name_of_your_new_branch`. Name the branch whatever you want, it could be "AddingNewFile" (without the quotations).

4) You are now automatically inside of the new branch instead of master. Check this using `git branch`.

### Now feel free to make all the changes you want. You can add new files, modify existing ones, etc.

5) When you made your changes to the project, use the following commands one at a time while inside the project folder.

```
git add --all 
git commit -m "Modified the changes."
git push origin [name of branch]
```

### Now you have a branch on github containing your changes, but now you want to merge your branch with the main branch so that your changes are visible alongside everyone else's.

6) Go to https://github.com/anthonysg/CS3307_Project in your browser.

7) Click the 'New Pull Request' button. Then in the second dropdown box, select the branch you just worked with.

8) Fix errors if there are any. Click the 'Create Pull request' button.

9) Click the 'Merge' Button as long as there are no errors. Otherwise you need to follow github's instructions to fix any conflicting lines of code or whatever.

10) You are done, now go back to git and use `git checkout master` to switch back to the main branch and use `git pull` to fetch the changes you just made. 

