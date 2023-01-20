/**
 * @file main2.c
 * @author your name (you@domain.com)
 * @brief mol.h that contains your typedefs, structure definitions and function prototypes
 * @version 0.1
 * @date 2023-01-10
 *
 * @copyright Copyright (c) 2023
 *
 */


#ifndef _mol_h
#define _mol_h
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Structures and Typedefs */
typedef struct atom // atom ADT
{
    char element[3];
    double x, y, z;
} atom;

typedef struct bond // bond ADT
{
    atom *a1, *a2;
    unsigned char eparis;
} bond;

typedef struct molecule
{
    unsigned short atom_max, atom_no;
    atom *atoms, **atom_ptrs;
    unsigned short bond_max, bond_no;
    bond *bonds, **bond_ptrs;
} molecule;

typedef double xform_matrix[3][3];

/* Function Prototypes */
// Functions for the atom
void atomset(atom *atom, char element[3], double *x, double *y, double *z); // setter for atom
void atomget(atom *atom, char element[3], double *x, double *y, double *z); // getter for atom

// Functions for the bond
void bondset(bond *bond, atom *a1, atom *a2, unsigned char epairs); // setter for bond
void bondget(bond *bond, atom **a1, atom **a2, unsigned char *epairs);

// Functions for the molecule
molecule *molmalloc(unsigned short atom_max, unsigned short bond_max); // dym. allocate space for the molecule -> return pointer of type malloc
molecule *molcopy(molecule *src);
void molfree(molecule *ptr);
void molappend_atom(molecule *molecule, atom *atom);
void molappend_bond(molecule *molecule, bond *bond);

void molsort(molecule *molecule);
void printHello(void);

#endif