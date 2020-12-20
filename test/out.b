Minishell:>
-----
Exec:command:
Arg0:arg0quote:
-----
Minishell:>
-----
Exec:command:
Arg0:arg0quote quote:
Arg1:arg2:
-----

-----
Exec:command2:
Pipe to:command:
-----
Minishell:>
-----
Exec:000aaaa\bbb:
-----
Minishell:>
-----
Exec:000aaa"bbb:
-----
Minishell:>
-----
Exec:000aaa\\bbb:
-----
Minishell:>
-----
Exec:000aaa$bbb:
-----
