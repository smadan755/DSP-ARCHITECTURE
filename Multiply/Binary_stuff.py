


def inv(num):
    num = list(str(num))

    for i in range(len(num)):
        if num[i] == "0":
            num[i] = "1"
        elif num[i] == "1":
            num[i] = "0"


    output = "".join(num)  # Reconstruct the binary string
    binary_result = output

    return binary_result


def twos_complement(binary):

    # Step 1: Invert the binary number
    inverted = inv(binary)

    # Step 2: Convert the inverted binary string to an integer
    inverted_int = int(inverted, 2)

    # Step 3: Add 1 to the inverted integer
    twos_comp_int = inverted_int + 1

    # Step 4: Convert back to binary, preserving the same bit length
    twos_comp_binary = bin(twos_comp_int)[2:]  # Remove '0b' prefix
    twos_comp_binary = twos_comp_binary.zfill(len(binary))  # Ensure same length as input

    return twos_comp_binary


def bin_add(bin1, bin2):

    # Step 1: Determine the bit length
    max_len = max(len(bin1), len(bin2))

    # Step 2: Pad the binary numbers to the same length
    bin1 = bin1.zfill(max_len)
    bin2 = bin2.zfill(max_len)

    # Step 3: Convert both to integers using two's complement if needed
    if bin1[0] == "1":  # If bin1 is negative
        bin1_dec = -int(twos_complement(bin1), 2)
    else:  # Positive number
        bin1_dec = int(bin1, 2)

    if bin2[0] == "1":  # If bin2 is negative
        bin2_dec = -int(twos_complement(bin2), 2)
    else:  # Positive number
        bin2_dec = int(bin2, 2)

    # Step 4: Add the two integers
    result_dec = bin1_dec + bin2_dec

    # Step 5: Convert the result back to binary
    if result_dec < 0:  # If the result is negative
        # Convert to binary, take two's complement, and preserve bit length
        result_binary = twos_complement(bin(abs(result_dec))[2:].zfill(max_len))
    else:  # Positive result
        result_binary = bin(result_dec)[2:].zfill(max_len)

    # Ensure the result fits within the original bit length
    if len(result_binary) > max_len:
        result_binary = result_binary[-max_len:]  # Truncate extra bits

    return result_binary


def right_shift(binary, bits):

    # Get the sign bit (first bit)
    sign_bit = binary[0]

    # Perform the shift by slicing and padding with the sign bit
    shifted = sign_bit * bits + binary[:-bits]

    return shifted




def booth_shift(A, B):
    combined = A + B  # Concatenate A and B
    sign_bit = combined[0]  # Preserve the sign bit for arithmetic shift

    # Perform arithmetic right shift
    shifted = sign_bit + combined[:-1]  # Shift right and preserve sign bit

    # Split back into A and B
    A = shifted[:len(A)]  # Take the first len(A) bits for A
    B = shifted[len(A):]  # Take the rest for B

    return A, B