#### Unable to remove file from git tracking: [Reference](https://stackoverflow.com/questions/57187693/how-to-fix-vscode-tracking-in-gitignore)
As there can be three types of files(tracked, untracked, and ignored). The files which are already tracked or indexed can't be ignored just by adding them to the .gitignore. Rather their index should be deleted. Then if you add them in the .gitignore it will be ignored.

Suppose you have a tracked file in the root named test.txt now you are adding this file to the .gitignore. It will not work unless you remove it from the git index like below

```
git rm --cached test.txt
```
Also, you can use the relative path of a file to remove it if they are not in the root.

Then the index will be deleted and git will stage them as files deleted but they won't be deleted from your local.