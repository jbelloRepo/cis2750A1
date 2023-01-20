#include "mol.h"

int main(int argc, char **argv)
{
    double x, y, z;     // position of atom relative to molecule
    atom a1, a2, a3;    // variable for atoms of type (atom)
    bond bond1, bond2;  // variable for bond of type (bond)
    molecule *molecule; // (pointer) variable for molecule of type (molecule)

    /* set the atoms */
    x = 2.5369;
    y = -0.1550;
    z = 0.0000;
    atomset(&a1, "O", &x, &y, &z); //* Function call

    x = 3.0739;
    y = 0.1550;
    z = 0.0000;
    atomset(&a2, "H", &x, &y, &z); //* Function call

    x = 2.0000;
    y = 0.1550;
    z = 0.0000;
    atomset(&a3, "H", &x, &y, &z); //* Function call

    molecule = molmalloc(3, 2);
    // printf("address of molecule_ptr in main file: %p\n", (void *)molecule);
    // printf("The atom max is: %d \n", molecule->atom_max);
    // printf("The bond max is: %d \n", molecule->bond_max);

    int i = 0;
    int j = 0;
    do
    {
        molappend_atom(molecule, &a1);
        printf("\n");
        printf("The atom max is: %d \n", molecule->atom_max);
        printf("After the molappend, the atom in the 0 index is: %s \n", molecule->atoms[j].element);
        j += 1;
        printf("After the molappend, the number of atoms in atoms is: %hu \n\n", molecule->atom_no);

        molappend_atom(molecule, &a2);

        printf("The atom max is: %d \n", molecule->atom_max);
        printf("After the molappend, the atom in the 1 index is: %s \n", molecule->atoms[j].element);
        j += 1;
        printf("After the molappend, the number of atoms in atoms is: %hu \n\n", molecule->atom_no);

        molappend_atom(molecule, &a3);
        printf("The atom max is: %d \n", molecule->atom_max);
        printf("After the molappend, the atom in the 2 index is: %s \n", molecule->atoms[j].element);
        j += 1;
        printf("After the molappend, the number of atoms in atoms is: %hu \n\n", molecule->atom_no);

        i += 1;
    } while (i < 2); //? Tested with i<10000; at which point atom max = 49152

    printf("==================================== This is for bondset() =============================================================================\n");
    bondset(&bond1, &(molecule->atoms[0]), &(molecule->atoms[1]), 1);
    printf("Address pointed to by molecule->atoms[0] & (molecule->atoms[1]: %p & %p \n", (void *)&(molecule->atoms[0]), (void *)&(molecule->atoms[1])); //! error checking
    bondset(&bond2, &(molecule->atoms[0]), &(molecule->atoms[2]), 1);
    printf("Address pointed to by molecule->atoms[0] & (molecule->atoms[2]: %p & %p \n", (void *)&(molecule->atoms[0]), (void *)&(molecule->atoms[2])); //! error checking
    printf("===========================================================================================================================================\n");
    printf("\n");

    /* add the bonds */
//     int k = 0;
//     int l = 0;
//     do{
//         molappend_bond(molecule, &bond1);
//     molappend_bond(molecule, &bond2);

// k+=1;
//     } while (i<2);
    molfree(molecule);

    return 0;
}
