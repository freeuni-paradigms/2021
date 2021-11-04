// Owner size = 8
    // age  offset=0, size=4
    // name offset=4, size=4

// Car size = 16
    // mileage offset=0, size=4
    // lights  offset=4, size=4
    // owner   offset=8, size=8


SP = SP - 10; // Make space for local variables

// Line 1: int l = 0;
M[SP + 6] = 0;          // Store 0 to l

// Line 2: int r = n;
R1 = M[SP + 18];        // Load n
M[SP + 2] = R1;         // Store n into r

// Line 3: while (l < r) {
R1 = M[SP + 6];         // Load l
R2 = M[SP + 2];         // Load r
BGE R1, R2 PC + 26 * 4; // Compare l and r

// Line 4: short m = (l + r) / 2;
R1 = M[SP + 6];         // Load l
R2 = M[SP + 2];         // Load r
R3 = R1 + R2;           // l + r
R4 = R3 / 2;            // (l + r) / 2
M[SP] = .2 R4;          // Store result in m

// Line 5: r = m;
R1 = .2 M[SP];          // Load m
M[SP + 2] = R1;         // Store m in r

// Line 6: if (cmp_fn((Owner *)(cars[m].lights)->name, person) < 0) {
SP = SP - 8;            // Allocate space for cmp_fn args
R1 = M[SP + 22];        // cars
R2 =.2 M[SP + 8];       // m
R3 = R2 * 16;           // m * sizeof(Car)
R4 = R1 + R3;           // &cars[m]
R5 = R4 + 4;            // &cars[m].lights
R6 = R5 + 4;            // &(Owner *)(cars[m].lights)->name
R7 = M[R6];             // Value of name
M[SP] = R7;             // Store first argument
R1 = M[SP + 30];        // person
M[SP + 4] = R1;         // Store second argument
R1 = M[SP + 34];        // Load cmp_fn address
CALL R1;                // Call it
SP = SP + 8;            // Dealocate space for cmp_fn args
BGE RV, 0 PC + 3 * 4;   // Compare return value to zero

// Line 7: l = m;
R1 = .2 M[SP];          // Load m
M[SP + 6] = R1;         // Store m in l
JMP PC - 28 * 4;        // Jump back to the while loop

// Line 8: return l;
RV = M[SP + 6];         // Load l into RV

SP = SP + 10;           // Deallocate space for local variables
RET;                    // Return