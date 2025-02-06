from Binary_stuff import inv, twos_complement, bin_add, booth_shift

# Initialize registers
B = "100110"  # Multiplier
C = "110111"   # Multiplicand
A = "000000"  # Accumulator

print("Initial A:", A)
print("Initial B:", B)

for _ in range(len(B)-1):
    # Extract B1 and B0 (last two bits of B)
    B0 = B[-1]
    B1 = B[-2]
    B1B0 = f"{B1}{B0}"

    # Perform Booth's algorithm operations
    if B1B0 == "10":
        A = bin_add(twos_complement(C), A)  # Subtract C from A
    elif B1B0 == "01":
        A = bin_add(C, A)  # Add C to A

    # Perform combined shift on A and B
    A, B = booth_shift(A, B)

    print("A:", A)
    print("B:", B)

# Final result: Combine A and B (ignoring B0)
final_product = A + B[:-1]  # Ignore B0
print("Final Product:", final_product)

