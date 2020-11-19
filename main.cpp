/**
 * Author: cptwunderlich
 * based on program by "Zh, a.i., davon,AI_Zuerich"
 * 19.11.2020
**/
#include <iostream>
#include <string>

// Some useful constants
const int none = -1; // No edge
const int err = 16;
const std::string yes{"yes"};
const std::string no{"no"};

// We have a directed graph, with at most two edges.
// We'll call them "yes" and "no". They store the index of target node.
// Negative values are sentinels meaning "no edge".
class node {
  public:
    const std::string text;
    const int yes;
    const int no;
    
    bool terminal() {
        return yes == none && no == none;
    }
};

int main() {
    // There are 16 + 1 nodes (one error state)
    node graph[] = {
        node{ "Are you using a prepostion?\n", 2, 1 },
        node{ "Is it the SUBJECT of the sentence?\nExample:The MAN buys a dog.\n", 4, 3 },
        node{ "Are you using ||aus, bei, mit, nach, seit, von, zu or gegenüber||?\n", 7, 5 },
        node{ "Is it after ||sein|| (the verb to be)?\nE.g.: The dog is a PUPPY.\n", 4, 6 },

        // Terminal node "nominative"
        node{ "You have NOMINATIVE:\n\nm. [der/ein]\nf. [die/eine]\nnt. [des/ein]\npl. [dir/meine]\n", none, none},
        
        node{ "Are you using \n||an, auf, hinter , in, neben, über, vor or zwischen?\n", 8, 12 },
        node{ "Is it after ||folgen, helfen glauben or begegnen?||\n", 7, 9 },
        
        // Terminal node "dative"
        node{ "You have DATIVE:\n\nm. [dem/einem]\nf. [der/einer]\nnt. [dem/einem]\npl. [den/meinen]\n", none, none},

        node{ "Is movement from A to B indicated?\n", 11, 7 },
        node{ "Is it the INDIRECT OBJECT?\nAre you translating the idea of ||to|| or ||for||\n", 7, 10 },
        node{ "Is it the DIRECT OBJECT?\nE.g.: The man buys a Dog\n", 11, 13 },
        
        // Terminal node "accusative"
        node{ "You have ACCUSATIVE:\n\nm. [den/einen]\nf. [die/eine]\nnt. [das/ein]\npl. [die/meine]\n", none, none},

        node{ "Are you using ||bis, durch, für, gegen, wider, ohne, um or entlang||?\n", 11, 15 },
        node{ "Are you showing possession??\nE.g.: That is my MOTHER'S room.\n", 14, err },
        
        // Terminal node "genitive"
        node{ "You have GENITIVE:\n\nm. [des/eines]\nf. [der/einer]\nnt. [des/eines]\npl. [der/meiner]\n", none, none},

        node{ "Are you using ||trotz, während, wegen or innerhalb||?\n", 14, err },
        
        node{ "Error. Invalid input!\n", none, none }
    };
    
    std::string inp{"no"}; // Initializing this makes sure, that 'inp' is never undefined, even if I skip reading from cin
    int tmp = 0;
    // Start at node 0, loop while in bounds
    for (int pos = 0; pos >= 0 && pos < err;) {
    
        // Print message and read user input
        std::cout << graph[pos].text;
        
        // Only read user input if this is not a terminal node
        if (!graph[pos].terminal()) {
            std::cin >> inp;
        }

        if (inp == yes) {
            tmp = graph[pos].yes;
        } else if (inp == no) {
            tmp = graph[pos].no;
        } else {
            std::cout << "Unrecognized answer. Please use 'yes' or 'no'.\n";
            continue; // Back to the top
        }
        
        // If we have an invalid selection, print error,
        // but don't change position. So we repeat the question.
        if (tmp == err) {
            std::cout << graph[err].text;
        } else {
            pos = tmp;
        }
    }

	return 0;
}
