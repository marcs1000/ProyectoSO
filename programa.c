#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char nombre[30];
	char consulta [200];
	conn = mysql_init(NULL);
	if (conn==NULL) 
	{
		printf ("Error al crear la conexion: %u %s\n", 
		mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "juego",0, NULL, 0);
	if (conn==NULL) 
	{
		printf ("Error al inicializar la conexion: %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	printf("Escribe el nick del jugador que quieras saber que partidas ha ganado:\n");
	scanf("%s",nombre);
	sprintf(consulta, "SELECT PARTIDA.ID FROM (JUGADOR, PARTIDA)WHERE PARTIDA.GANADOR = JUGADOR.NICK AND JUGADOR.NICK = '%s'",nombre);
	err= mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		while (row !=NULL) {
			printf ("Las partidas que %s ha ganado son: %s\n", nombre, row[0]);
			// obtenemos la siguiente fila
			row = mysql_fetch_row (resultado);
	}
		mysql_close (conn);
		exit(0);
}
