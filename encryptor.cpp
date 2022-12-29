#include <iostream>
#include <openssl/sha.h>

int main() {
  // Create a new SHA-256 encryptor
  SHA256_CTX encryptor;
  SHA256_Init(&encryptor);

  // Encrypt a string using the encryptor
  const char* message = "hello world";
  SHA256_Update(&encryptor, message, strlen(message));

  // Get the encrypted hexadecimal digest of the string
  unsigned char digest[SHA256_DIGEST_LENGTH];
  SHA256_Final(digest, &encryptor);

  // Print the encrypted hexadecimal digest of the string
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    printf("%02x", digest[i]);

  return 0;
}
