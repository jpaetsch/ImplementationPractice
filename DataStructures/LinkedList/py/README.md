# Python Double Linked List - implementation practice

## Table of Contents
* [Summary](#summary)
* [Setup & Usage](#setup-&-usage)
* [Technologies](#technologies)
* [Inspiration](#inspiration)
* [Sources](#sources)

## Summary
A class based double linked list implementation with good starting functionality.

## Setup & Usage
'python linkedlist.py' - Run the program

## Potential Improvements
A number of potential improvements including:
* Cleaning/tightening up of some of the functions especially 'reverse_this_list(self)'
* Add a tail node to take better care of edge cases (would also help with the above improvement)
* Increase number of operations including a node insertion one
* Override '__str__()' instead of having the current print function
* More/better test cases

## Technologies
This project is created with:
* Python (version 3.8.0)
* pyenv-virtualenv extension for virtual environment management\
Note for setting up auto-activating Python virtualenv:\
'pyenv virtualenv <version> <name>' - set up a new named, versioned virtualenv\
'pyenv local <name>' - set the current directory to automatically activate this shell\

## Inspiration
Double linked list adds additional functionality - also before now Python has mainly been a scripting or jupyter notebooks machine learning language for me so working with classes instead is good practice.

## Sources
Looked at various online sources if I got stuck with a particular operation but programmed it from scratch.\
[Website for pyenv & virtualenv setup](https://towardsdatascience.com/managing-virtual-environment-with-pyenv-ae6f3fb835f8)