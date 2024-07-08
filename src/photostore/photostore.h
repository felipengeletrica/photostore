/********************************************************************
Copyright (c) 2014-2018, Felipe Vargas <felipeng.eletrica@gmail.com>
 FileName:      photostore.h
 programmer:    Felipe Vargas
 version: See version control (git server)

*******************************************************************/

/************************** Includes ******************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../db/sqlite/sqlite3.h"


/************************** Defines  *******************************/

#define SIZE_NAME_MODEL 100
#define SIZE_NAME_MANU 100
#define SIZE_NAME_DESC 250
#define SIZE_ACCESSORY_OPTIONS 3
#define SIZE_BUFFER_QUERY    1000

#define true 0
#define false 1

/************************** Variables  *****************************/

static  char  *list_accessory[SIZE_ACCESSORY_OPTIONS] = {"Lens", "Flash", "Tripod"};
static char *database = "photostore.db";

/*\brief: Create tables with many-to-many relationships
 * with the tb_camera_accessory table, in addition
 * the cascade delete relationship is created.
 */
static char *sql_create_tables =
		"DROP TABLE IF EXISTS tb_camera;"
		"CREATE TABLE  tb_camera ("
		"id	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"model TEXT NOT NULL,"
		"manufacturer	TEXT NOT NULL,"
		"weight 	REAL NOT NULL,"
		"price	REAL NOT NULL,"
		"resolution REAL NOT NULL,"
		"wifi INTEGER NOT NULL);"

		"DROP TABLE IF EXISTS tb_accessory;"
		"CREATE TABLE  tb_accessory ("
		"id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"id_accessory INTEGER NOT NULL,"
		"manufacturer TEXT NOT NULL,"
		"Descrition 	TEXT,"
		"price	REAL"
		");"

		"DROP TABLE IF EXISTS tb_camera_accessory;"
		"CREATE TABLE tb_camera_accessory("
		"camera_id INTEGER,"
		"accessory_id INTEGER,"
		"FOREIGN KEY(camera_id) REFERENCES tb_camera(id) ON DELETE CASCADE,"
		"FOREIGN KEY(accessory_id) REFERENCES tb_accessory(id) ON DELETE CASCADE"
		");"
		"DROP INDEX IF EXISTS camera_index;"
		"CREATE INDEX camera_index ON tb_camera_accessory(camera_id);"
		"DROP INDEX IF EXISTS accessory_index;"
		"CREATE INDEX accessory_index ON tb_camera_accessory(accessory_id);";

/* \brief: Insert cameras in table tb_camera
 */
static char *sql_insert_cam =
		"INSERT INTO tb_camera("
		"model,"
		"manufacturer,"
		"weight,"
		"price,"
		"resolution,"
		"wifi)"
		"VALUES("
		"'%s',"
		"'%s',"
		"%d,"
		"%.2f,"
		"%.2f,"
		"%d);";

/*
 * \brief: Insert cameras accessories
 */
static char *sql_insert_acces =
		"INSERT INTO tb_accessory("
		"id_accessory, "
		"manufacturer, "
		"Descrition, "
		"price)"
		"VALUES("
		"%d,"
		"'%s',"
		"'%s',"
		"%.2f);";

/*
 * \brief: Insert cameras accessories with model cam
 */
static char *sql_insert_acces_with_model =
		"BEGIN TRANSACTION; "
		"INSERT INTO tb_accessory("
		"id_accessory, "
		"manufacturer, "
		"Descrition, "
		"price)"
		"VALUES("
		"%d,"
		"'%s',"
		"'%s',"
		"%.2f);"
		"INSERT INTO tb_camera_accessory("
		"camera_id,"
		"accessory_id)"
		"VALUES("
		"(SELECT id FROM tb_camera WHERE "
		"model = '%s' ),  last_insert_rowid());"
		"COMMIT";

/*
 * \brief: Consult cameras by model
 */

static char *sql_select_cam_by_model =
		"SELECT * FROM  tb_camera "
		"WHERE "
		"model LIKE '%s%s';";
/*
 * \brief: Consult camera by model and return acesssories
 */
static char *sql_select_cam_by_model_ret_access =

		"SELECT  tb_accessory.id, "
		"tb_accessory.id_accessory, "
		"tb_accessory.manufacturer, "
		"tb_accessory.Descrition, "
		"tb_accessory.price "
		"FROM "
		"tb_camera, "
		"tb_accessory, "
		"tb_camera_accessory "
		"WHERE "
		"tb_camera.id = tb_camera_accessory.camera_id "
		"AND tb_accessory.id = tb_camera_accessory.accessory_id "
		"AND tb_camera.model LIKE '%s%s' "
		"order by tb_accessory.id_accessory asc, tb_accessory.price asc;";

/*
 * \brief: Consult all cameras
 */
static char *sql_select_all_cam =
		"SELECT * FROM  tb_camera;";

/*
 * \brief: Consult all cameras
 */
static char *sql_select_all_accessory =
		"SELECT * FROM  tb_accessory;";

/*
 * \brief: Delete camera
 */
static char *sql_delete_cam =
		"DELETE from tb_camera "
		"where model = '%s'";

/*
 * \brief: Delete accessory
 */
static char *sql_delete_accessory =
		"DELETE from tb_accessory "
		"where id = '%d'";

/*
 * \brief: Update camera
 */
static char *sql_update_camera =
		"UPDATE tb_camera "
		"SET "
		"manufacturer = '%s',"
		"weight = %d,"
		"price = %.2f,"
		"resolution = %.2f,"
		"wifi = %d "
		"WHERE "
		"model = '%s';";

/*
 * \brief: Update accessory
 */
static char *sql_update_acessory =
		"UPDATE tb_accessory "
		"SET "
		"id_accessory = %d,"
		"manufacturer = '%s',"
		"Descrition = '%s',"
		"price = %.2f "
		"WHERE "
		"id = %d;";


/************************** Enumerates *****************************/
typedef enum
{
	lens,
	flash,
	tripod
}en_accessory;

/************************* Structs ********************************/

//Camera
typedef struct
{
	int id;
	char model[SIZE_NAME_MODEL];
	char manufacturer[SIZE_NAME_MANU];
	int weight;
	float price;
	float resolution;
	int  wifi;
}st_camera;

//Accessory
typedef struct
{
	int id;
	en_accessory accessory;
	char manufacturer[SIZE_NAME_MANU];
	char descrition[SIZE_NAME_DESC];
	float price;

}st_accessory;

//Generic struct table
typedef struct
{
	void *table;
	uint32_t rows;
	uint32_t columns;
}st_datatable;

//Database
typedef struct {
    sqlite3 *db;
    sqlite3_stmt *res;
    char *zErrMsg;
}st_database;


/********************** Prototypes *********************************/
int insert_cam(st_database *database_st, st_camera *camera_st);
int insert_acess(st_database *database_st, st_accessory *acessory_st, char *cam_model);
int remove_cam(st_database *database_st, int idcam);
int remove_acess(st_database *database_st, int idacess);
int consult_list_cam_ad_acess(st_database *database_st, char *cam_model);
int consult_access(st_database *database_st, int idcam);
int consult_cam(st_database *database_st, char *cam_model);
int consult_acess(st_database *database_st, char *cam_model);
int consult_allcam(st_database *database_st);
int consult_allacess(st_database *database_st);
int delete_cam(st_database *database_st, char *model);
int delete_acess(st_database *database_st, int id);
int update_cam(st_database *database_st, st_camera *camera_st);
int update_acess(st_database *database_st, st_accessory *acessory_st);
int createdatabase(st_database *database_st);
void showcam(st_datatable *datatable_camera_st);
//Database
static int callback(void *data, int argc, char **argv, char **azColName);
int database_execute(char *sql, int withcallback);

st_database *sqlite3_connect(const char *filedb);
void database_close(st_database *database_st);
int database_execute_v3(st_database *database, const char *sql);
void database_set_row_count(st_database *database, uint32_t * row);
st_datatable *fetch_all_access(st_database *database_st);
st_datatable *fetch_all_cam(st_database *database_st);


