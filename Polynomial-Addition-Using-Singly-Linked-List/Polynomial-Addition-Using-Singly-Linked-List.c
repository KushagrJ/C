// This program is unfinished.

// There should be at least one term in each polynomial.
// The user should not enter multiple like terms. For eg., 2x + 5x, etc.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node
{
    int coefficient;
    char* variables;
    int* exponents;
    struct node* next;
} Node;


// For eg., let one term of a polynomial be 2 x^2 b^-1 i.
// coefficient - 2.
// var[0] - 'x', var[1] - 'b', var[2] - 'i', var[3] - '\0'.
// exp[0] - number of variables (i.e. 3), exp[1] - exponent of 'x' (i.e. 2),
// exp[2] - exponent of 'b' (i.e. -1), exp[3] - exponent of 'i' (i.e. 1).


int get_next_non_space_character(void);

// Ensure that the node that is passed to this function is not the last node.
void delete_after_node(Node*);


int main(void)
{

    Node* head_term = NULL;
    Node* current_term;
    Node* previous_term;

    // To store temporary characters.
    int c;

    printf("Enter polynomial 1: ");

    bool overall_sign_of_current_term_is_minus = false;

    c = get_next_non_space_character();
    if (c == '-')
        overall_sign_of_current_term_is_minus = true;
    else
        ungetc(c, stdin);

    // This outer loop controls the individual terms in a polynomial.
    // Breaking out of this loop means that the polynomial does not contain any
    // more terms.
    while (true)
    {
        current_term = malloc(sizeof (Node));
        if (current_term == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        current_term->coefficient = 1;

        int assumed_number_of_variables_in_current_term = 5;

        current_term->variables =
            malloc(assumed_number_of_variables_in_current_term * sizeof (char));
        if (current_term->variables == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        current_term->exponents =
            malloc(assumed_number_of_variables_in_current_term * sizeof (int));
        if (current_term->exponents == NULL)
        {
            fprintf(stderr, "Unsuccessful allocation\n");
            exit(EXIT_FAILURE);
        }

        // It doesn't matter whether this scanf() succeeds or fails.
        scanf("%d", &(current_term->coefficient));

        if (overall_sign_of_current_term_is_minus)
            current_term->coefficient *= -1;

        // This index is for the variable-exponent combinations in the current
        // term.
        int index = 0;

        // This inner loop controls the individual variable-exponent
        // combinations in the current term.
        // Breaking out of this loop means that the current term does not
        // contain any more variable-exponent combinations.
        while (true)
        {
            c = get_next_non_space_character();

            if (c == '+')
            {
                // Applies to the next iteration of the outer loop.
                overall_sign_of_current_term_is_minus = false;

                break;
            }

            else if (c == '-')
            {
                // Applies to the next iteration of the outer loop.
                overall_sign_of_current_term_is_minus = true;

                break;
            }

            else if (c == '\n')
            {
                break;
            }

            else   // i.e. c should be a variable.
            {
                if (index == assumed_number_of_variables_in_current_term - 1)
                {
                    assumed_number_of_variables_in_current_term *= 2;

                    char* temp_1 =
                        realloc(current_term->variables,
                                assumed_number_of_variables_in_current_term *
                                    sizeof (char));
                    if (temp_1 == NULL)
                    {
                        fprintf(stderr, "Unsuccessful allocation\n");
                        exit(EXIT_FAILURE);
                    }
                    current_term->variables = temp_1;

                    int* temp_2 =
                        realloc(current_term->exponents,
                                assumed_number_of_variables_in_current_term *
                                    sizeof (int));
                    if (temp_2 == NULL)
                    {
                        fprintf(stderr, "Unsuccessful allocation\n");
                        exit(EXIT_FAILURE);
                    }
                    current_term->exponents = temp_2;
                }

                (current_term->variables)[index] = (char) c;
                (current_term->exponents)[index + 1] = 1;

                c = getchar();   // c should either be ' ', '^' or '\n'.
                if (c == '^')
                    scanf("%d", &((current_term->exponents)[index + 1]));

                (index)++;

                if (c == '\n')
                    break;
            }
        }

        (current_term->variables)[index] = '\0';
        (current_term->exponents)[0] = index;

        if (head_term == NULL)
            head_term = current_term;
        else
            previous_term->next = current_term;
        current_term->next = NULL;

        // Applies to the next iteration of the outer loop.
        previous_term = current_term;

        if (c == '\n')
            break;
    }

    current_term = head_term;
    while (current_term)
    {
        printf("%d ", current_term->coefficient);
        printf("%s ", current_term->variables);
        for (int i = 1; i <= (current_term->exponents)[0]; i++)
            printf("%d ", (current_term->exponents)[i]);
        printf("\n");
        current_term = current_term->next;
    }

    while (head_term)
    {
        Node* temp_node = head_term;
        head_term = head_term->next;
        free(temp_node->variables);
        free(temp_node->exponents);
        free(temp_node);
    }

    return 0;

}


int get_next_non_space_character(void)
{

    int c;

    while ((c = getchar()) == ' ')
        continue;

    return c;

}
