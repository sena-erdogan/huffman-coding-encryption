# huffman-encoding-encryption

Huffman coding is a data compression method used in computer science to compress data without loss. One of the biggest advantages of Huffman coding is that it makes an encoding according to the frequencies of the characters used, so that the frequently used characters take up less space.
Huffman encoding initially takes a large text as input, containing all the characters to be used later, if possible. The frequencies of the characters included in this large text (frequency of occurrence in the text) will determine the structure of the binary tree to be created. There are "characters" in the leaves of this binary tree, which is created by using the frequencies of the characters. During the movement from root to leaves (i.e., characters), codes of characters will be obtained when each left branch is referenced with the bit '0' and each right branch with the bit '1'.
The frequency of a character also refers to the level of compression. The more frequently a character is used, the more bits can be expressed in the Huffman coding tree.

The program
- Takes a text file (reference.txt) as input, creating the Huffman coding tree, and encrypting each character
- Encrypts a text requested from the user with character codes created from the coding tree and writes it in a .dat file (encoded.dat)
- Decodes the binary array in encoded.dat and writes it to decoded.txt
- Calculates the file size difference between encryption (encoded.dat) and decryption (decoded.txt)

Assignment from the Computer Programming course (GTU, 2020)
