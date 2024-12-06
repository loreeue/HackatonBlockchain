#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/stylus_utils.h"
#include "../stylus-sdk-c/include/storage.h"
#include "../stylus-sdk-c/include/string.h"

// buffer used to write output, avoiding malloc
uint8_t	buf_out[32];

// succeed and return a bebi32
ArbResult	inline _return_success_bebi32(bebi32 const retval)
{
	ArbResult res = {Success, retval, 32};
	return res;
}

ArbResult	hola_mundo(uint8_t *input, size_t len)
{
	return _return_short_string(Success, "Hola Mundo Loreto");
}

int	handler(size_t argc) //argc es la cantidad de bytes que tenemos
{
	// Save the function calldata (selector(bytes4) + fn_args(bytes))
	uint8_t	argv[argc];
	read_args(argv); // 4 btes (firma del a funcion)

	// Define the registry array with registered functions
	FunctionRegistry	registry[] = {
	// balance()
	// address: 0x82B36e0c4C6E9cafA5CeACf481fa13e6CE2ac385
	// uint256: 100000000000000000000....32bytes
	// string: "242242121"
	// bytes32: 0x82B36ac385
	{to_function_selector("prueba()"), hola_mundo}, // Add more functions as needed here
	//de manera externa se llama prueba y hola_mundo es el nombre de la función a implementar
	};

	uint32_t	signature = *((uint32_t *)argv); // Take function selector

	// Call the function based on the signature
	ArbResult	res = call_function(registry,
		sizeof(registry) / sizeof(registry[0]),
			signature, argv + 4, argc - 4 // Exclude the selector from calldata
	);
	return (write_result(res.output, res.output_len), res.status);
}

ENTRYPOINT(handler)
