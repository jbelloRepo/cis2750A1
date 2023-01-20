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
    printf("The string read from char array is: %s \n", atom->element);
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

        /* Reallocating Memory (ATOM) */

#ifdef DEBUG_ON
        printf("The (ATOM) array is now full. REALLOCATING!!!....\n"); //! error checking
#endif
                                                                       // *(molecule->atoms) = (atom *)realloc(molecule->atoms, molecule->atom_max);
        a1 = (struct atom *)realloc(molecule->atoms, molecule->atom_max * sizeof(struct atom)); // you cannot use atom* here
#ifdef DEBUG_ON
        printf("Address pointed to by {molecule->atoms} (old memory address): %p\n", (void *)molecule->atoms);     //! error checking
        printf("Address pointed to by {temp a1} in header file (new memory address #REALLOC): %p\n", (void *)a1); //! error checking
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
            printf("Address assigned by {temp a1} to {molecule->atoms} in header file (new memory address #REALLOC): %p\n", (void *)molecule->atoms); //! error checking
#endif
        }

        a2 = (struct atom **)realloc(molecule->atom_ptrs, molecule->atom_max * sizeof(struct atom *));
#ifdef DEBUG_ON
        printf("Address pointed to by {molecule->atom_ptr} (old memory address): %p\n", (void *)molecule->atom_ptrs); //! error checking
        printf("Address pointed to by {temp a2} in header file (new memory address #REALLOC) : %p\n", (void *)a2);    //! error checking
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
            printf("Address assigned by {temp a2} to {molecule->atom_ptrs} in header file(new memory address #REALLOC) : %p\n", (void *)molecule->atom_ptrs); //! error checking
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
        molecule->atom_ptrs[molecule->atom_no] = &molecule->atoms[molecule->atom_no]; // pointer to the first atom
        molecule->atom_no += 1;                                                       // increment after addition
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

void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs) //* setter for the bond variable
{
    bond->a1 = a1;
    bond->a2 = a2;
#ifdef DEBUG_ON
    printf("Address pointed to by bond->a1 in the header file: %p\n", (void *)bond->a1); //! error checking
    printf("Address pointed to by bond->a2 in the header file: %p\n", (void *)bond->a2); //! error checking
#endif
    bond->eparis = epairs;
}

void molappend_bond(molecule *molecule, bond *bond)
{ //! bond_no initially set to 0

    struct bond *b1, **b2;

    if (molecule->bond_no == molecule->bond_max) //* check if bond_no and bond_max are equal
    {
        if (molecule->bond_max == 0) //! TEST THIS when bond_max = 0
        {
            molecule->bond_max += 1; //* add 1 if bond_max = 0
        }
        molecule->bond_max *= 2; //* double size of bond_max

        /* Reallocating Memory (BOND) */

#ifdef DEBUG_ON
        printf("\nThe (BOND) array is now full. REALLOCATING!!!....\n"); //! error checking
#endif

        b1 = (struct bond *)realloc(molecule->bonds, molecule->bond_max * sizeof(struct bond)); // you cannot use atom* here

#ifdef DEBUG_ON
        printf("Address pointed to by {molecule->bonds} (old memory address): %p\n", (void *)molecule->bonds);     //! error checking
        printf("Address pointed to by {temp b1} in header file (new memory address #REALLOC): %p\n", (void *)b1); //! error checking
#endif

        if (b1 == NULL) //! add more statements or return 0 --CHECK THIS
        {
#ifdef DEBUG_ON
            printf("No additional heap for atoms *atom \n");
#endif
        }
        else
        {

            molecule->bonds = b1;
#ifdef DEBUG_ON
            printf("Address assigned by {temp b1} to {molecule->bonds} in header file (new memory address #REALLOC): %p\n", (void *)molecule->bonds); //! error checking
#endif
        }

        b2 = (struct bond **)realloc(molecule->bond_ptrs, molecule->bond_max * sizeof(struct bond *));
#ifdef DEBUG_ON
        printf("Address pointed to by {molecule->bond_ptr} (old memory address): %p\n", (void *)molecule->bond_ptrs); //! error checking
        printf("Address pointed to by {temp b2} in header file (new memory address #REALLOC): %p\n", (void *)b2);    //! error checking
#endif

        if (b2 == NULL) //! add more statements or return 0 --CHECK THIS
        {
#ifdef DEBUG_ON
            printf("No additional heap for atom **atoms \n");
#endif
        }
        else
        {
            molecule->bond_ptrs = b2;
#ifdef DEBUG_ON
            printf("Address assigned by {temp b2} to molecule->bond_ptrs in header file(new memory address #REALLOC) : %p \n\n", (void *)molecule->bond_ptrs); //! error checking
#endif
        }
    }

    if ((molecule->bond_no > 0) && (molecule->bond_no < molecule->bond_max)) //* check bond_no is greater than 0 and lesser than bond_max
    {
        molecule->bonds[molecule->bond_no].a1 = bond->a1; //* assign the first member from parameter passed to molecule
        molecule->bonds[molecule->bond_no].a2 = bond->a2;
        molecule->bonds[molecule->bond_no].eparis = bond->eparis;
        molecule->bond_ptrs[molecule->bond_no] = &molecule->bonds[molecule->bond_no]; //! CHECK THIS
        molecule->bond_no += 1;                                                       // increment after addition
    }

    if ((molecule->bond_no == 0) && (molecule->bond_max != 0)) //* check if the molecule is initially empty (executes for first element only)
    {
        //! index is static for first element in array[0]
        molecule->bonds[0].a1 = bond->a1; //* assign the first member from parameter passed to molecule
        molecule->bonds[0].a2 = bond->a2;
        molecule->bonds[0].eparis = bond->eparis;
        molecule->bond_ptrs[0] = &molecule->bonds[0]; //! CHECK THIS
        molecule->bond_no += 1;

#ifdef DEBUG_ON
        printf("Address pointed to by molecule->bond_ptrs[0] in header file : %p\n", (void *)molecule->bond_ptrs[0]); //! error checking
        
#endif
    }
    printf("The value of bond_max is %d \n", molecule->bond_max);
    printf("The number of bonds currently in the molecule is: %d \n", molecule->bond_no);
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
