#include <gtest/gtest.h>
extern "C" {
    #include "./incl/minishell.h"
}

void    help()
{
    printf("minishell, version 0.1.1-release \
These shell commands are defined internally.  Type `help` to see this list. \
Type `help name` to find out more about the function `name`. \
Use `info bash` to find out more about the shell in general. \
Use `man -k` or `info` to find out more about commands not in this list. \
\
A star (*) next to a name means that the command is disabled.\
\
cd [-L|[-P [-e]] [-@]] [dir]\
echo [-neE] [arg ...]\
env\
export [-fn] [name[=value] ...] or export -p\
unset [-f] [-v] [-n] [name ...]");
}

TEST(Tests, HelpTest) {
    testing::internal::CaptureStdout();
    std::string expected = "minishell, version 0.1.1-release \
These shell commands are defined internally.  Type `help` to see this list. \
Type `help name` to find out more about the function `name`. \
Use `info bash` to find out more about the shell in general. \
Use `man -k` or `info` to find out more about commands not in this list. \
\
A star (*) next to a name means that the command is disabled.\
\
cd [-L|[-P [-e]] [-@]] [dir]\
echo [-neE] [arg ...]\
env\
export [-fn] [name[=value] ...] or export -p\
unset [-f] [-v] [-n] [name ...]";
	help();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, expected);
}
