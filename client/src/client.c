#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	if (config == NULL) {
    // ¡No se pudo crear el config!
		log_info(logger, "No se pudo crear el config!");
		// Terminemos el programa
		abort();
	}

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	valor = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	
	// Loggeamos el valor de config

	log_info(logger, "La clave es: %s", valor);
	log_info(logger, "La IP es: %s", ip);
	log_info(logger, "El puerto es: %s", puerto);


	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	/*---------------------------------------------------PARTE FINAL-------------------------------------------------------------*/

	terminar_programa(conexion, logger, config);

	return 0;
}

/*---------------------------------------------------FUNCIONES-------------------------------------------------------------*/

t_log* iniciar_logger() {
	t_log* nuevo_logger = log_create("tp0.log", "CLIENTE", true, LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config() {
	t_config* nuevo_config = config_create("/home/utnso/tp0/client/cliente.config");
	return nuevo_config;
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}

void leer_consola(t_log* logger) {
    char* leido;

    while ((leido = readline("> ")) != NULL) {
        if (strcmp(leido, "exit") == 0) {
            free(leido);
            break;
        }

        log_info(logger, "Leí: %s", leido);
        free(leido);
    }
}