#include "../include/stylus_sdk.h"
#include "../stylus-sdk-c/include/stylus_utils.h"
#include "../stylus-sdk-c/include/storage.h"
#include "../stylus-sdk-c/include/string.h"
#include "../stylus-sdk-c/include/hostio.h"

// Buffer para salida
uint8_t	buf_out[32];

// Función de éxito para devolver resultados
ArbResult	inline _return_success_bebi32(bebi32 const retval)
{
	ArbResult res = {Success, retval, 32};
	return res;
}

// Función para almacenar datos del usuario
ArbResult	store_user(uint8_t *input, size_t len)
{
	if (len < 33)
	{ // ID (32 bytes) + al menos 1 byte de datos
        return _return_short_string(Failure, "Invalid input length");
	}

	// Separar ID de los datos
	uint8_t user_id[32];
	memcpy(user_id, input, 32);

	uint8_t *user_data = input + 32;
	size_t data_len = len - 32;

	// Generar hash del ID del usuario
	uint8_t key_hash[32];
	native_keccak256(user_id, 32, key_hash);

	// Almacenar los datos, respetando su longitud
	storage_load_bytes32(key_hash, user_data); // Este método almacena solo 32 bytes.

	// Si los datos exceden 32 bytes, agregar lógica para almacenarlos en partes.
	if (data_len > 32)
	{
		uint8_t extended_key_hash[32];
		native_keccak256(key_hash, 32, extended_key_hash);

		// Almacenar datos adicionales desde el índice 32 en adelante
		storage_load_bytes32(extended_key_hash, user_data + 32);
	}

	return _return_short_string(Success, "User Stored");
}

ArbResult	add_file(uint8_t *input, size_t len)
{
	if (len < 33)
	{ // ID (32 bytes) + al menos 1 byte de datos
		return _return_short_string(Failure, "Invalid input length");
	}

	// Separar ID de los datos
	uint8_t file_id[32];
	memcpy(file_id, input, 32);

	uint8_t *file_data = input + 32;
	size_t data_len = len - 32;

	// Generar hash del ID del archivo
	uint8_t key_hash[32];
	native_keccak256(file_id, 32, key_hash);

	// Almacenar los datos del archivo
	storage_load_bytes32(key_hash, file_data);

	// Manejar datos adicionales si exceden 32 bytes
	if (data_len > 32)
	{
		uint8_t extended_key_hash[32];
		native_keccak256(key_hash, 32, extended_key_hash);

		storage_load_bytes32(extended_key_hash, file_data + 32);
	}

	return _return_short_string(Success, "File Added");
}

ArbResult	approve_update(uint8_t *input, size_t len)
{
	if (len < 33) { // ID (32 bytes) + al menos 1 byte de datos
		return _return_short_string(Failure, "Invalid input length");
	}

	// Separar ID de los datos
	uint8_t update_id[32];
	memcpy(update_id, input, 32);

	uint8_t *update_data = input + 32;
	size_t data_len = len - 32;

	// Generar hash del ID de la actualización
	uint8_t key_hash[32];
	native_keccak256(update_id, 32, key_hash);

	// Almacenar los datos de la actualización
	storage_load_bytes32(key_hash, update_data);

	// Manejar datos adicionales si exceden 32 bytes
	if (data_len > 32)
	{
		uint8_t extended_key_hash[32];
		native_keccak256(key_hash, 32, extended_key_hash);

		storage_load_bytes32(extended_key_hash, update_data + 32);
	}

	return _return_short_string(Success, "Update Approved");
}

ArbResult	reward_contributor(uint8_t *input, size_t len)
{
	if (len < 33)
	{ // ID (32 bytes) + al menos 1 byte de datos
		return _return_short_string(Failure, "Invalid input length");
	}

	// Separar ID de los datos
	uint8_t contributor_id[32];
	memcpy(contributor_id, input, 32);

	uint8_t *reward_data = input + 32;
	size_t data_len = len - 32;

	// Generar hash del ID del contribuyente
	uint8_t key_hash[32];
	native_keccak256(contributor_id, 32, key_hash);

	// Almacenar los datos de la recompensa
	storage_load_bytes32(key_hash, reward_data);

	// Manejar datos adicionales si exceden 32 bytes
	if (data_len > 32)
	{
		uint8_t extended_key_hash[32];
		native_keccak256(key_hash, 32, extended_key_hash);
		storage_load_bytes32(extended_key_hash, reward_data + 32);
	}

	// Responder con un valor de recompensa fijo (1)
	static const uint8_t ONE_BEBI32[32] = { [31] = 1 }; // Todo ceros, con 1 en el byte menos significativo
	return _return_success_bebi32(ONE_BEBI32);
}

int	handler(size_t argc)
{
	uint8_t argv[argc];
	read_args(argv);

	FunctionRegistry registry[] = {
		{to_function_selector("storeUser()"), store_user},
	};

	uint32_t signature = *((uint32_t *)argv);

	ArbResult res = call_function(registry,
		sizeof(registry) / sizeof(registry[0]),
		signature,
		argv + 4,
		argc - 4);

	return (write_result(res.output, res.output_len), res.status);
}

// Define el punto de entrada
ENTRYPOINT(handler)
