#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/stylus_utils.h"
#include "../stylus-sdk-c/include/storage.h"
#include "../stylus-sdk-c/include/string.h"

// Buffer for writing output, avoids dynamic memory allocation (malloc)
uint8_t	buf_out[32];

// Helper function: Returns a successful ArbResult containing a 32-byte integer
ArbResult	inline _return_success_bebi32(bebi32 const retval)
{
	// Create an ArbResult with Success status and the provided retval
	ArbResult res = {Success, retval, 32};
	return res;
}

void store(const char* key, const uint8_t* value, size_t len) {
	// Convert the key to a 32-byte value using Keccak256
	uint8_t key_hash[32];
	native_keccak256((uint8_t *)key, strlen(key), key_hash);

	// Store the first 32 bytes of the value using `storage_store_bytes32`
	storage_store_bytes32(key_hash, value);
}


// Function to register a user and store their role
ArbResult register_user(uint8_t *input, size_t len)
{
	// Store the user role data in persistent storage under the key "user_role"
	store("user_role", input, len);
	// Return success with a short string response
	return _return_short_string(Success, "User Registered");
}

// Function to add a file by storing its hash
ArbResult add_file(uint8_t *input, size_t len)
{
	// Store the file hash in persistent storage under the key "file_hash"
	store("file_hash", input, len);
	// Return success with a short string response
	return _return_short_string(Success, "File Added");
}

// Function to approve updates for files or data
ArbResult approve_update(uint8_t *input, size_t len)
{
	// Store the approval data under the key "update_approval"
	store("update_approval", input, len);
	// Return success with a short string response
	return _return_short_string(Success, "Update Approved");
}

// Function to reward contributors by updating their reward balance
ArbResult reward_contributor(uint8_t *input, size_t len)
{
	// Store the reward balance under the key "reward_balance"
	store("reward_balance", input, len);

	// Return success with a 32-byte integer response (1 as the default value)
	static const uint8_t ONE_BEBI32[32] = { [31] = 1 }; // All 0s, with 1 in the least significant byte
	return _return_success_bebi32(ONE_BEBI32);
}

// Main handler function for processing incoming calls
int	handler(size_t argc)
{
	// Allocate a buffer to store the call arguments (function selector + parameters)
	uint8_t	argv[argc];
	read_args(argv); // Read the calldata into the buffer

	// Define the registry of functions supported by this contract
	FunctionRegistry registry[] = {
		// Map the external function names to their corresponding internal implementations
		{to_function_selector("registerUser()"), register_user},
		{to_function_selector("addFile()"), add_file},
		{to_function_selector("approveUpdate()"), approve_update},
		{to_function_selector("rewardContributor()"), reward_contributor},
	};

	// Extract the 4-byte function selector from the calldata
	uint32_t	signature = *((uint32_t *)argv);

	// Call the appropriate function based on the selector and pass the arguments
	ArbResult	res = call_function(registry,
		sizeof(registry) / sizeof(registry[0]),	// Number of functions in the registry
		signature,								// Function selector
		argv + 4,								// Skip the first 4 bytes (selector)
		argc - 4								// Remaining arguments length
	);

	// Write the result to the output and return the status
	return (write_result(res.output, res.output_len), res.status);
}

// Define the entry point for the contract
ENTRYPOINT(handler)
