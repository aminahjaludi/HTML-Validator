#include "HTMLChecker.h"


HTMLChecker::HTMLChecker() {
    self_closing_tags = {
            "<!doctype>", "<area>", "<base>", "<br>", "<col>", "<embed>", "<hr>",
            "<img>", "<input>", "<link>", "<meta>", "<param>", "<source>", "<track>", "<wbr>",
            "<!doctype/>", "<area/>", "<base/>", "<br/>", "<col/>", "<embed/>", "<hr/>",
            "<img/>", "<input/>", "<link/>", "<meta/>", "<param/>", "<source/>", "<track/>", "<wbr/>"
    };
}

/**
 * Takes the path of a html file and loads it into a
 * Queue one word at a time.  The method reads in the file
 * one character at a time, using a state machine with 4
 * states to parse the tags and words into a Queue for later
 * evaluation.
 *
 * @param file_path
 * @return true if the file could be read.
 */
bool HTMLChecker::load(const string &file_path) {
    // open the file and make sure there is something in it.
    fstream file_in(file_path, fstream::in);
    bool is_empty = file_in.peek() == std::ifstream::traits_type::eof();
    if (is_empty) return false;

    string buff = "";            // holds the word or tag string as we build it.
    char character;              // holds the char we read from the file
    State state = whitespace;    // set our initial state to whitespace

    // loop though each char in the file
    while (file_in >> noskipws >> character) {

        if (state == whitespace) {
            if (!isspace(character)) {
                // if you find a < is the start of a tag
                // otherwise its the start of a word
                if (character == '<') state = tag;
                else state = word;
                buff = character;
            }
        } else if (state == tag) {
            // if it's a > we've reached the end of the tag
            if (character == '>') {
                buff += '>';
                state = whitespace;
                // add the tag to the heml elements queue
                html_elements.push(buff);
                buff = "";

            } else if (isspace(character)) {
                // space in the tag means we're looking at attributes
                state = tag_attr;
            } else {
                buff += tolower(character);
            }
        } else if (state == tag_attr) {
            // in the tag attributes ignore everything but the >
            if (character == '>') {
                buff += '>';
                html_elements.push(buff);
                buff = "";
                state = whitespace;
            }
        } else if (state == word) {
            if (isspace(character)) {
                html_elements.push(buff);
                buff = "";
                state = whitespace;
            } else if (character == '<') {
                html_elements.push(buff);
                buff = "";
                state = tag;
                buff += character;
            } else {
                buff += character;
            }
        }
    }
    return true;
}

bool HTMLChecker::isValid()
{
    stack<string> tags; //create stack to hold the opening tags

    //while there are still elements left in the queue
    while(!html_elements.empty())
    {
        //store the current front of the queue in a string variable
        string front = html_elements.front();

        //if the front is not a closing tag
        if(self_closing_tags.count(front) == 0)
        {
            //check if the first character of the front is "<"
            if((html_elements.front()).substr(0,1) == "<")
            {
                //check if the "<" is followed by a "/" (meaning it's a closing tag)
                if(front.substr(1,1) == "/")
                {
                    if(tags.empty()) //if there are no opening tags return false
                    {
                        return false;
                    }

                    //string variable to hold the tag stack's top, without the '<' and '>' characters
                    string opening_tag = (tags.top()).substr(1, (tags.top()).length() - 1 );

                    //comparing the opening and closing tags without the '<', '>', and '/' characters
                    if(opening_tag == front.substr(2, front.length() - 1))
                    {
                        //if the tags match then pop the opening tag
                        tags.pop();
                    }
                    else //if they don't match return false
                    {
                        return false;
                    }
                }
                else //if the front is an opening tag, push it to the stack
                {
                    tags.push(html_elements.front());
                }
            }
        }

        //move to the next html element by popping the front
        html_elements.pop();
    }

    //if the html_elements queue is empty, return true. otherwise, return false.
    return (tags.empty());
}