#include <gtest/gtest.h>
extern "C" {
#include "../incl/minishell.h"
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
        ASSERT_STREQ(*data->envp, *expecteddata);
        data->envp++;
        expecteddata++;
    }
}

TEST(Test, GetCMDListTest)
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
    envp.push_back(strdup("PATH=/nfs/homes/voparkan/bin:/nfs/homes/voparkan/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"));
    auto *data = new t_data;
    data_init(data, envp.data());
    std::string envpath = getenv("PATH");
    std::string expect_envpath = "/nfs/homes/voparkan/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    ASSERT_EQ(envpath, expect_envpath);
    char	**folder_strs = NULL;
    folder_strs = (char**) malloc(sizeof(char *) * (get_number_of_folders(getenv("PATH")) + 1));
    get_folders(getenv("PATH"), folder_strs);
    // while (*folder_strs)
    // {
    //     std::cout << "folders:\n";
    //     std::cout << *folder_strs;
    //     std::cout << "\n";
    //     folder_strs++;
    // }
    scan_folders(folder_strs, data);
    get_cmd_list(data);
    add_cmd_list_node("pwd", "/usr/bin", data);
    add_cmd_list_node("ls", "/usr/bin", data);
    char *path = get_cmd_path("ls", data);
    ASSERT_STREQ(path, "/usr/bin/ls");
    path = get_cmd_path("pwd", data);
    // std::cout << "path for pwd:\n";
    // std::cout << path;
    // std::cout << "\n";
    ASSERT_STREQ(path, "/usr/bin/pwd");
}