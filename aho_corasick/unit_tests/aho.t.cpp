#include "../src/aho_corasick.h"

#include <limits.h>
#include <string>
#include <gtest/gtest.h>

using namespace std;
using namespace ACS;

TEST(aho_corasick, empty_source_match_empty) {
    // GIVEN
    string empty_string = "";
    ACSearch seacher(empty_string);

    // WHEN
    int ret = seacher.match(empty_string);

    // THEN
    EXPECT_EQ(-1, ret);
}

TEST(aho_corasick, empty_source_match_normal_pattern) {
    // GIVEN
    string empty_string = "";
    ACSearch seacher("pattern");

    // WHEN
    int ret = seacher.match(empty_string);

    // THEN
    EXPECT_EQ(-1, ret);
}

TEST(aho_corasick, normal_source_match_normal_pattern) {
    // GIVEN
    string pattern = "hello";
    string source = "The first word he said is hello";
    ACSearch seacher(pattern);

    // WHEN
    int ret = seacher.match(source);

    // THEN
    EXPECT_EQ(source.find(pattern), ret);
}


TEST(aho_corasick, normal_source_doesnot_match_pattern) {
    // GIVEN
    string pattern = "not_exist";
    string source = "The first word he said is hello";
    ACSearch seacher(pattern);

    // WHEN
    int ret = seacher.match(source);

    // THEN
    EXPECT_EQ(-1, ret);
}

TEST(aho_corasick, long_source_match_pattern) {
    // GIVEN
    string pattern = "hello";
    string source = "This sets up an auto command that fires after any "
        "filetype-specific plugin; the command removes the three flags "
        "from the 'formatoptions' option that control hello the automatic "
        "insertion of comments. With this in your vimrc, a comment "
        "character will not be automatically inserted in the next line under any situation.";
    ACSearch seacher(pattern);

    // WHEN
    int ret = seacher.match(source);

    // THEN
    EXPECT_EQ(source.find(pattern), ret);
}

TEST(aho_corasick, long_source_match_long_pattern) {
    // GIVEN
    string pattern = "with Ctrl/Cmd+Click, and opening links or going to definition can be invoked";
    string source = "Multi-cursor modifier If you'd like to change the modifier key for applying"
                        " multiple cursors to Cmd+Click on macOS and Ctrl+Click on Windows and Linux,"
                        "you can do so with the editor.multiCursorModifier setting. This lets users "
                        "coming from other editors such as Sublime Text or Atom continue to use the "
                        "keyboard modifier they are familiar with. The setting can be set to: ctrlCmd"
                        " - Maps to Ctrl on Windows and Cmd on macOS alt - The existing default Alt. "
                        "There's also a menu item Use Ctrl+Click for Multi-Cursor in the Selection menu"
                        " to quickly toggle this setting. The Go To Definition and Open Link gestures "
                        "will also respect this setting and adapt such that they do not conflict. "
                        "For example, when the setting is ctrlCmd, multiple cursors can be added "
                        "with Ctrl/Cmd+Click, and opening links or going to definition can be invoked with Alt+Click.";
    ACSearch seacher(pattern);

    // WHEN
    int ret = seacher.match(source);

    // THEN
    EXPECT_EQ(source.find(pattern), ret);
}



