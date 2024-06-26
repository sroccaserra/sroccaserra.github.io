-- title: Coding kata starter in Python
-- date: 2023-07-19

This is how I usually start a coding kata, here in Python. It should be easy
and very fast, so I can move on to the kata (the interesting part).

Rationale: some kata repositories provide a starter in many languages. If this
works for you this is great, you might not need this article. This article is
intended to people that want to quickly start from scratch (because I find it
to be rather easy), and / or people that have found that this or that
repository does not use your version of the runtime, or uses old versions of
testing libraries, or does not use your favorite libraries, or are even slower
than starting from scratch.

So here is what I use. It should take less that 3 mn (you can practice to go
even faster than that), and give you a shareable public repository ready to
write tests and have a linter ready for fast feedback. Now we can move on to
the kata.

If you find that useful, you can go further and adapt it to your prefered
testing lib or your prefered language.

Prerequisite: have a Python 3 runtime available. Usually this also provides
virtualenv. If not: `sudo apt install virtualenv`.

Let's suppose we have chosen to practice with the famous Bowling kata.

Project start:

<pre>
$ <b>mkdir</b> bowling-kata
$ <b>cd</b> bowling-kata
</pre>

Create a virtualenv, activate it (⚠️ shell dependent ⚠️) and install pytest.

<pre>
$ <b>virtualenv</b> -p python3 venv
$ <b>source</b> venv/bin/activate
$ <b>pip</b> install pytest
</pre>

Note: if you know & prefer the unittest module from the Python standard lib,
you don't even need this virtualenv & pytest installation step.

Write the shortest possible failing test in your favorite editor in "bowling_test.py", for example:

<pre>
<b>def</b> test_fails()<b>:</b>
    <b>assert</b> 0 <b>==</b> 1
</pre>

Run the test, it should fail with the correct error message:

<pre>
$ <b>pytest</b>
============================== test session starts ===============================
platform linux -- Python 3.10.6, pytest-7.4.0, pluggy-1.2.0
rootdir: /home/sebastien/Developer/scratch/bowling-kata
configfile: pytest.ini
collected 1 item

bowling_test.py F                                                          [100%]

==================================== FAILURES ====================================
___________________________________ test_fails ___________________________________

    def test_fails():
>       assert 0 == 1
<b>E       assert 0 == 1</b>

bowling_test.py:2: AssertionError
============================ short test summary info =============================
<b>FAILED bowling_test.py::test_fails - assert 0 == 1</b>
=============================== 1 failed in 0.01s ================================
(venv)

</pre>

For a learning session, you should be good to go. This is where I usually stop
the setup part and start working on the kata. Your IDE should catch most lint
errors already. Optional: `pip install flake8` if needed.

## (Optional) Create a more elaborate directory structure

<pre>
$ <b>mkdir</b> src
$ <b>mkdir</b> test
$ <b>mv</b> bowling_test.py test
</pre>

Add a bowling function in `src/bowling.py`:

<pre>
<b>def</b> bowling()<b>:</b>
    <b>return</b> 1
</pre>

Import it from `test/bowling_test.py`:

<pre>
<b>from</b> bowling <b>import</b> bowling

<b>def</b> test_fails()<b>:</b>
    <b>assert</b> 0 <b>==</b> bowling()
</pre>

Add `src` to pytest’s pythonpath in `pytest.ini`:

<pre>
[pytest]
pythonpath=src
</pre>

Running `pytest` again should give you the same correct error message.

The final structure:

<pre>
$ <b>tree</b> -I __pycache__/ -I venv -I .pytest_cache/
.
├── pytest.ini
├── src
│   └── bowling.py
└── test
    └── bowling_test.py
</pre>

## (Optional) Git setup

This is useful in remote contexts if you want to take turns in the session.

<pre>
$ <b>echo</b> venv >> .gitignore
$ <b>echo</b> __pycache__ >> .gitignore
$ <b>echo</b> .pytest_cache >> .gitignore
$ <b>git</b> init
$ <b>git</b> add .
$ <b>git</b> commit -m first
</pre>

Create a new repo on github or gitlab or ..., then copy / paste the github
provided snippet to setup the remote and push.

## Kata Animation tips

Always leave the test code, implementation code, and test logs visible at all
times. Use split windows, your IDE or tmux can help with that. This allows
everyone to have time to finish reading the code or the error messages at all
times.

Explicitely state that the primary goal is to have a shared understanding, not
to finish the kata at all cost.

Finish the session 10 mn early, use this time for a debrief. Listen to what
everyone wants to share about this particular session.

For a live coding session, learning to type code fast can help keeping the
session dynamic, and frees some time for the conversation. If the keyboard
changes hands, don't blame someone for typing slowly.

## Links

- The bowling kata ~ <https://codingdojo.org/kata/Bowling/>
- The Python 3 docs ~ <https://docs.python.org/3/>
- The Virtualenv docs ~ <https://virtualenv.pypa.io/en/latest/>
- The Pytest docs ~ <https://docs.pytest.org/>
- The unittest docs ~ <https://docs.python.org/3/library/unittest.html>
