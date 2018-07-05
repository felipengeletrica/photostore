/********************************************************************
Copyright (c) 2014-2018, Felipe Vargas <felipeng.eletrica@gmail.com>
 FileName:	photostore.c
 Author:    Felipe Vargas
 Version: 	See version control (git server)

********************************************************************/

/************************** Includes ******************************/
#include "photostore.h"

/************************** Variables  *****************************/

/*
 *\brief Connect SQLite database
 *\param *const char: database filename
 *\return st_database: not null sucess
 *\return st_database: null fail
 */
st_database *sqlite3_connect(const char *filedb)
{
    st_database *database_st;
    database_st = calloc(1, sizeof(st_database));

    if (database == NULL){
    		return NULL;
    }

    database_st->db = NULL;
    database_st->res = NULL;
    database_st->zErrMsg = 0;

    if (sqlite3_open(filedb, &(database_st)->db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database %s\n", sqlite3_errmsg(database_st->db));
        return NULL;
    }

    return database_st;
}

/*
 *\brief Disconnect SQLite database
 *\param *st_database: database pointer
 */
void database_close(st_database *database_st)
{
    sqlite3_finalize(database_st->res);
    sqlite3_close(database_st->db);
    free(database_st);
}

/*
 *\brief Execute sql query
 *\param *const char: Database pointer
 *\param *sql: Query
 *\return int: True
 *\return int: False
 */
int database_execute_v3(st_database *database_st, const char *sql)
{
	int ret = false;

	if (strcasestr(sql, "SELECT") &&
        !strcasestr(sql, "CREATE") &&
        !strcasestr(sql, "INSERT") &&
        !strcasestr(sql, "UPDATE") &&
        !strcasestr(sql, "DELETE")) {

        /* the old prepared statement object will be destroyed */
        sqlite3_finalize(database_st->res);
        /* the new prepared statement object will be created */
        ret = sqlite3_prepare_v2(database_st->db, sql, -1, &(database_st)->res, 0);
    }
    else
    {
    		ret = sqlite3_exec(database_st->db, sql, NULL, 0, &(database_st)->zErrMsg);
    }

    return ret;
}

/*
 *\brief Execute fetch cameras
 *\param *const char: Database pointer
 *\return *st_camera: List of cameras
 *\return *st_camera: NULL
 */
st_datatable *fetch_all_cam(st_database *database_st)
{
	uint32_t address = 0;
	uint32_t rows = 0;

	database_execute_v3(database_st, sql_select_all_cam);
	database_set_row_count(database_st, &rows);

	st_camera *camera_st = malloc(rows * sizeof(st_camera));
	if(camera_st == NULL){
		printf("Failed to allocate memory");
		return NULL;
	}

	while (sqlite3_step(database_st->res) != SQLITE_DONE){
		camera_st->id = sqlite3_column_int(database_st->res, 0);
	    strcpy(camera_st->model, (const char *restrict) sqlite3_column_text(database_st->res, 1));
	    strcpy(camera_st->manufacturer, (const char *restrict) sqlite3_column_text(database_st->res, 2));
	    camera_st->weight = sqlite3_column_int(database_st->res, 3);
	    camera_st->price = sqlite3_column_double(database_st->res, 4);
	    camera_st->resolution = sqlite3_column_double(database_st->res, 5);
	    camera_st->wifi = sqlite3_column_int(database_st->res, 6);
	    //showcam(camera_st);
	    camera_st++;
	    address++;
	    }

		st_datatable *dt_st = malloc(address * sizeof(st_camera));
		dt_st->table = (camera_st - address);
		dt_st->rows = address;
		dt_st->columns = 7;

		//free(camera_st);

		return dt_st;
}

/*
 *\brief Execute fetch accessory
 *\param *const char: Database pointer
 *\return *st_accessory: List of accessories
 *\return *st_accessory: NULL
 */
st_datatable *fetch_all_access(st_database *database_st)
{
	uint32_t address = 0;
	uint32_t rows = 0;

	database_execute_v3(database_st, sql_select_all_accessory);
	database_set_row_count(database_st, &rows);

	st_accessory *accessory_st = malloc(rows * sizeof(st_accessory));

	if(accessory_st == NULL){
		printf("Failed to allocate memory");
		return NULL;
	}

	while (sqlite3_step(database_st->res) != SQLITE_DONE){
		accessory_st->id = sqlite3_column_int(database_st->res, 0);
		accessory_st->accessory = sqlite3_column_int(database_st->res, 1);
	    strcpy(accessory_st->manufacturer, (const char *restrict) sqlite3_column_text(database_st->res, 2));
	    strcpy(accessory_st->descrition, (const char *restrict) sqlite3_column_text(database_st->res, 3));
	    accessory_st->price = sqlite3_column_double(database_st->res, 4);
	    accessory_st++;
	    address++;
	    }
		st_datatable * dt_st = malloc(address * sizeof(st_accessory));
		dt_st->table = (accessory_st - address);
		dt_st->rows = address;
		dt_st->columns = 5;
		//free(accessory_st);

		return dt_st;
}

/*
 *\brief Count lines as ruturnning query
 *\param *const char: Database pointer
 */
void database_set_row_count(st_database *database_st, uint32_t * row)
{

    sqlite3_reset(database_st->res);
    row = 0;

    while (sqlite3_step(database_st->res) != SQLITE_DONE){
    		row++;
    }

    sqlite3_reset(database_st->res);
}

/*
 *\brief Show data in pointer camera
 *\param *camera_st: struct camera
 */
void showcam(st_datatable *datatable_camera_st)
{
	st_camera * camera_st = datatable_camera_st->table;
	int rows = datatable_camera_st->rows;

	if(datatable_camera_st != NULL){
		printf("\n\r\t############## CAMERA ##############");
		for(int cont = 0; cont < rows; cont++){
			printf("\n\r\tid: %d", camera_st->id);
			printf("\n\r\tManufaturer: %s", camera_st->manufacturer);
			printf("\n\r\tModel: %s", camera_st->model);
			printf("\n\r\tPrice: %02f", camera_st->price);
			printf("\n\r\tResolution: %02f", camera_st->resolution);
			printf("\n\r\tWeight: %d", camera_st->weight);
			printf("\n\r\tWifi: %s", camera_st->wifi == 0 ? "YES" : "NO");
			printf("\n\r");
			camera_st++;
		}
	}
}

/*
 *\brief Show data in pointer camera
 *\param *acessory_st: struct acessory
 */
void showaccessory(st_datatable *datatable_acessory_st)
{
	st_accessory * accessory_st = datatable_acessory_st->table;
    int rows = datatable_acessory_st->rows;

    if(datatable_acessory_st != NULL){
    		printf("\n\r\t############## ACCESSORIES ##############");
		for(int cont = 0; cont < rows; cont++){
			printf("\n\r\tid: %d", accessory_st->id);
			printf("\n\r\tManufaturer: %s", accessory_st->manufacturer);
			printf("\n\r\tModel: %s", accessory_st->descrition);
			printf("\n\r\tPrice: %02f", accessory_st->price);
			printf("\n\r");
			accessory_st++;
		}
	}
}

/*
 *\brief Show data after consult
 *\param *data: Received for handler
 *\param argc: Number lines received
 *\param argv: Collum data
 *\param azColName: Collum name
 */
static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	//fprintf(stderr, "%s: ", (const char*)data);
	for(i=0; i<argc; i++){
		printf("\t");
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	 }
	printf("\n");
	return 0;
}


/*
 *\brief Show data after consult
 *\param *sql: SQL query
 *\return true: Success execute query
 *\return false: Error execute query
 */
int database_execute(char *sql, int withcallback)
{
	sqlite3 *db;
	char *err_msg = 0;
	const char* data = "Callback function called";

	int rc = sqlite3_open(database, &db);
	if (rc != SQLITE_OK){
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	rc = sqlite3_exec(db, sql,
			(withcallback == true ?  callback : 0),
			(withcallback == true ?  (void*)data : 0), &err_msg);

	if (rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
		sqlite3_close(db);
		return 1;
	}
	sqlite3_close(db);
	return 0;
}

/*
 *\brief Create new portable SQLite Database
 *\return true: Success create new database
 *\return false: Error create new database
 */
int createdatabase(st_database *database_st)
{
	return database_execute(sql_create_tables, false);
}


/*
 *\Brief Insert new camera in database
 *\param *camera_st: Camera struct
 *\return true: Success create new database
 *\return false: Error create new database
 */
int insert_cam(st_database *database_st, st_camera *camera_st)
{
	int ret = false;
	char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);

	sprintf(sql,
			sql_insert_cam,
			camera_st->model,
			camera_st->manufacturer,
			camera_st->weight,
			camera_st->price,
			camera_st->resolution,
			camera_st->wifi
			);
	ret = database_execute_v3(database_st, sql);
	free(sql);

	return ret;
}

/*
 *\Brief Insert new accessory
 *\param *database_st: Database pointer
 *\param *st_accessory: Accessory
 *\param *cam_model: add acessory a camera
 *\return true: Success create new database
 *\return false: Error create new database
 */
int insert_acess(st_database *database_st, st_accessory *acessory_st, char *cam_model)
{
	int ret = false;
	char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);
	sprintf(sql,
			sql_insert_acces_with_model,
			acessory_st->accessory,
			acessory_st->manufacturer,
			acessory_st->descrition,
			acessory_st->price,
			cam_model);
	ret = database_execute_v3(database_st, sql);

	free(sql);
	return ret;
}

/*
 *\Brief: Consult camera model
 *\param *database_st: Pointer database
 *\param *camera_st: Camera struct
 *\return true: Success consult cameras
 *\return false: Error consult cameras
 */
int consult_cam(st_database *database_st, char *cam_model)
{
	int ret = false;
	/* Return camera model */
	char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);

	sprintf(sql,
			sql_select_cam_by_model,
			cam_model,
			"%");
	ret = database_execute(sql, true);
	free(sql);

	return ret;
}

/*
 *\Brief: Consult camera model
 *\param *camera_st: Camera struct
 *\return true: Success consult cameras
 *\return false: Error consult cameras
 */
int consult_acess(st_database *database_st, char *cam_model)
{
	int ret = false;

	/* Return acessories compatibles */
    char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);
	sprintf(sql,
			sql_select_cam_by_model_ret_access,
			cam_model,
			"%");
	ret = database_execute(sql, true);
	free(sql);
	return ret;
}

/*
 *\Brief: Consult camera model
 *\camera_st: Camera struct
 *\returning camreras and acessories compatibles
 *\return true: Success consult cameras
 *\return false: Error consult cameras
 */
int consult_list_cam_ad_acess(st_database *database_st, char *cam_model)
{
	int ret = false;

    printf("---------------------------- CAMERA MODEL ----------------------------\n\r");
	ret = consult_cam(database_st, cam_model);
	if(ret != 0) return ret;
	 printf("---------------------------- ACESSORIES ----------------------------\n\r");
	ret = consult_acess(database_st, cam_model);

	return ret;
}

/*
 *\Brief: Consult all cameras
 *\return true: Success consult cameras
 *\return false: Error consult cameras
 */
int consult_allcam(st_database *database_st)
{
	int ret = false;
	/* Return acessories compatibles */
	ret = database_execute(sql_select_all_cam, true);
	return ret;

}

/*
 *\Brief: Consult all accessories
 *\return true: Success consult accessories
 *\return false: Error consult accessories
 */
int consult_allacess(st_database *database_st)
{
	int ret = false;
	/* Return acessories compatibles */
	ret = database_execute(sql_select_all_accessory, true);
	return ret;
}

/*
 *\Brief: Delete camera
  *\param *database_st: Camera struct
 *\param *camera_st: Camera struct
 *\return true: Success
 *\return false: Error
 */
int delete_cam(st_database *database_st, char *model)
{
	int ret = false;
	char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);
	sprintf(sql, sql_delete_cam, model);
	ret = database_execute_v3(database_st, sql);
	free(sql);
	return ret;

}

/*
 *\Brief: Delete Accessory
 *\param *database_st: Pointer database
 *\param id: accessory id
 *\return true: Success
 *\return false: Error
 */
int delete_acess(st_database *database_st, int id)
{
	int ret = false;
	char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);
	sprintf(sql, sql_delete_accessory,id);
	ret = database_execute_v3(database_st, sql);
	free(sql);
	return ret;
}

/*
 *\Brief: Delete Accessory
 *\param *database_st: Pointer database
 *\param *camera_st: Camera struct
 *\return true: Success
 *\return false: Error
 */
int update_cam(st_database *database_st, st_camera *camera_st)
{
	int ret = false;
	char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);
	sprintf(sql,
			sql_update_camera,
			camera_st->manufacturer,
			camera_st->weight,
			camera_st->price,
			camera_st->resolution,
			camera_st->wifi,
			camera_st->model);
	ret = database_execute_v3(database_st, sql);
	free(sql);
	return ret;

}

/*
 *\Brief: update Accessory
 *\param *database_st: Pointer database
 *\param *acessory_st: Camera struct
 *\return true: Success
 *\return false: Error
 */
int update_acess(st_database *database_st, st_accessory *acessory_st)
{
	int ret = false;
	char *sql = malloc(sizeof(char) * SIZE_BUFFER_QUERY);
	sprintf(sql,
			sql_update_acessory,
			acessory_st->accessory,
			acessory_st->manufacturer,
			acessory_st->descrition,
			acessory_st->price,
			acessory_st->id);
	ret = database_execute_v3(database_st, sql);
	free(sql);
	return ret;
}
