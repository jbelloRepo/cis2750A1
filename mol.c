#include "mol.h"
#define DEBUG_ON // for debugging

/************************************
******** Function Definition ********
************************************/

/*********************
Functions for the atom
*********************/

void atomset(atom *atom, char element[3], double *x, double *y, double *z) // setter for atom
{
    //* Copy elements into struct members
    strcpy(atom->element, element); // strcpy to struct
    atom->x = *x;
    atom->y = *y;
    atom->z = *z;

#ifdef DEBUG_OFF
    // printf("The char character is: %c \n", element[0]);
    // printf("The char character is: %c \n", element[1]);
    // printf("The char character is: %c \n", element[2]);
    printf("The char character is: %s \n", atom->element);
#endif
}

/*************************
Functions for the molecule
**************************/

molecule *molmalloc(unsigned short atom_max, unsigned short bond_max) // dym. allocate space for the molecule -> return pointer of type malloc
{
    molecule *molecule_ptr = (molecule *)malloc(sizeof(molecule)); //* allocate molecule on the heap
#ifdef DEBUG_OFF
    printf("address of molecule_ptr in header file : %p\n", (void *)molecule_ptr);
#endif
    if (molecule_ptr != NULL) //* allocate space for "atoms" array & atom_ptrs
    {
        molecule_ptr->atom_max = atom_max;
        molecule_ptr->atom_no = 0;                                     // set to 0 initially
        molecule_ptr->atoms = (atom *)malloc(atom_max * sizeof(atom)); // unsigned short vs int
#ifdef DEBUG_OFF
        printf("address of molecule_ptr->atoms in header file : %p\n", (void *)molecule_ptr->atoms); //! error checking
#endif
        molecule_ptr->atom_ptrs = (atom **)malloc(atom_max * sizeof(atom *));
        molecule_ptr->bond_max = bond_max;
        molecule_ptr->bonds = (bond *)malloc(atom_max * sizeof(bond));
        molecule_ptr->bond_ptrs = (bond **)malloc(atom_max * sizeof(bond *));
        molecule_ptr->bond_no = 0; // set to 0 initially
    }
    // molecule *mol_malloced_address = (molecule *)malloc(sizeof(molecule)); // pointer to molecule
    return molecule_ptr;
}

void molappend_atom(molecule *molecule, atom *atom)
{
    struct atom *a1, **a2; //! TEMP VARS

    if (molecule->atom_no == molecule->atom_max) //* check atom_no & atom_max before appending to array
    {
        if (molecule->atom_max == 0) //! TEST THIS when atom_max = 0
        {
            molecule->atom_max += 1; //* add 1 if atom_max = 0
        }
        molecule->atom_max *= 2; //* double size of atom_max

        /* Reallocating memory */

#ifdef DEBUG_ON
        printf("The array is now full. REALLOCATING!!!....\n"); //! error checking
#endif
                                                                // *(molecule->atoms) = (atom *)realloc(molecule->atoms, molecule->atom_max);
        a1 = (struct atom *)realloc(molecule->atoms, molecule->atom_max * sizeof(struct atom)); // you cannot use atom* here
#ifdef DEBUG_ON
        printf("Address pointed to by molecule->atoms(old memory address): %p\n", (void *)molecule->atoms);     //! error checking
        printf("Address pointed to by temp a1 in header file(new memory address #REALLOC) : %p\n", (void *)a1); //! error checking
#endif

        if (a1 == NULL) //! add more statements or return 0 --CHECK THIS
        {
#ifdef DEBUG_ON
            printf("No additional heap for atoms *atom \n");
#endif
        }
        else
        {

            molecule->atoms = a1;
#ifdef DEBUG_ON
            printf("Address assigned by temp a1 to molecule->atoms in header file(new memory address #REALLOC) : %p\n", (void *)molecule->atoms); //! error checking
#endif
        }

        a2 = (struct atom **)realloc(molecule->atom_ptrs, molecule->atom_max * sizeof(struct atom *));
#ifdef DEBUG_ON
        printf("Address pointed to by molecule->atom_ptr(old memory address): %p\n", (void *)molecule->atom_ptrs); //! error checking
        printf("Address pointed to by temp a2 in header file(new memory address #REALLOC) : %p\n", (void *)a2);    //! error checking
#endif
        if (a2 == NULL) //! add more statements or return 0 --CHECK THIS
        {
#ifdef DEBUG_ON
            printf("No additional heap for atom **atoms \n");
#endif
        }
        else
        {
            molecule->atom_ptrs = a2;
#ifdef DEBUG_ON
            printf("Address assigned by temp a1 to molecule->atoms in header file(new memory address #REALLOC) : %p\n", (void *)molecule->atom_ptrs); //! error checking
#endif
        }

        // free(a1); //? FREE THIS ?
        // free(a2);
    }

    if ((molecule->atom_no > 0) && (molecule->atom_no < molecule->atom_max)) //* check atom_no is greater than 0 and lesser than atom_max
    {
        strcpy(molecule->atoms[molecule->atom_no].element, atom->element);
        molecule->atoms[molecule->atom_no].x = atom->x;
        molecule->atoms[molecule->atom_no].y = atom->y;
        molecule->atoms[molecule->atom_no].z = atom->z;
        molecule->atom_ptrs[molecule->atom_no] = &molecule->atoms[0]; // pointer to the first atom
        molecule->atom_no += 1;                                       // increment after addition
    }

    if ((molecule->atom_no == 0) && (molecule->atom_max != 0)) //* check if the molecule is initially empty ( executes for first element only)
    {
        //! index is static for first element in array[0]
        strcpy(molecule->atoms[0].element, atom->element);
        molecule->atoms[0].x = atom->x;
        molecule->atoms[0].y = atom->y;
        molecule->atoms[0].z = atom->z;
        molecule->atom_ptrs[0] = &molecule->atoms[0]; // pointer to the first atom
        molecule->atom_no += 1;                       // increment after adding to atoms
#ifdef DEBUG_OFF
        printf("address pointed to by molecule->atom_ptrs[0] in header file : %p\n", (void *)molecule->atom_ptrs[0]); //! error checking
        printf("The value of atom_max is %d \n", molecule->atom_max);
#endif
    }
}

/*********************
Functions for the bond
**********************/

void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs)
{
    bond->a1 = a1;
    bond->a2 = a2;
#ifdef DEBUG_ON
    printf("Address pointed to by bond->a1 in the header file: %p\n", (void *)bond->a1); //! error checking
    printf("Address pointed to by bond->a2 in the header file: %p\n", (void *)bond->a2); //! error checking
#endif
    bond->eparis = epairs;
}

/*******************
Additional functions
********************/


// void molsort(molecule *molecule);

void molfree(molecule *ptr)
{
    free(ptr->atoms);
    free(ptr->atom_ptrs);
    free(ptr->bonds);
    free(ptr->bond_ptrs);
    free(ptr);
}

// void printHello(void)
// {
//     printf("Hello \n");
// }
