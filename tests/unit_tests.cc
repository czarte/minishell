#include <gtest/gtest.h>
extern "C" {
#include "../incl/minishell.h"
}

// void    help()
// {
//     printf("minishell, version 0.1.1-release \
// These shell commands are defined internally.  Type `help` to see this list. \
// Type `help name` to find out more about the function `name`. \
// Use `info bash` to find out more about the shell in general. \
// Use `man -k` or `info` to find out more about commands not in this list. \
// \
// A star (*) next to a name means that the command is disabled.\
// \
// cd [-L|[-P [-e]] [-@]] [dir]\
// echo [-neE] [arg ...]\
// env\
// export [-fn] [name[=value] ...] or export -p\
// unset [-f] [-v] [-n] [name ...]"));
// }

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

TEST(Tests, InitData)
{
    std::vector<char *> envp;
    envp.push_back(strdup("SHELL=/bin/zsh"));
    envp.push_back(strdup("SESSION_MANAGER=local/c3r1s3.42prague.com:@/tmp/.ICE-unix/1794201,unix/c3r1s3.42prague.com:/tmp/.ICE-unix/1794201"));
    envp.push_back(strdup("QT_ACCESSIBILITY=1"));
    envp.push_back(strdup("COLORTERM=truecolor"));
    envp.push_back(strdup("XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg"));
    envp.push_back(strdup("SSH_AGENT_LAUNCHER=gnome-keyring"));
    envp.push_back(strdup("XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session22"));
    envp.push_back(strdup("PWD=/nfs/homes/voparkan"));
    envp.push_back(strdup("KRB5CCNAME=FILE:/tmp/krb5cc_101745_ZLHYd6"));
    envp.push_back(strdup("LOGNAME=voparkan"));
    envp.push_back(strdup("XDG_SESSION_DESKTOP=ubuntu"));
    envp.push_back(strdup("XDG_SESSION_TYPE=x11"));
    envp.push_back(strdup("HOME=/nfs/homes/voparkan"));
    envp.push_back(strdup("LANG=en_US.UTF-8"));
    envp.push_back(strdup("XDG_CURRENT_DESKTOP=ubuntu:GNOME"));
    envp.push_back(strdup("VTE_VERSION=6800"));
    auto *data = new t_data;
    char **expecteddata = envp.data();
    data_init(data, envp.data());
    /*for (int i = envp.size() - 1; i >= 0; i--)
    {
        std::cout << envp[i];
        std::cout << "\n";
    }
    for (int i = envp.size() - 1; i >= 0; i--)
    {
        std::cout << data->envp[i];
        std::cout << "\n";
    }*/
    while (*data->envp)
    {
        EXPECT_EQ(*data->envp, *expecteddata);
        data->envp++;
        expecteddata++;
    }
}