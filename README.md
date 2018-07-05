

 <t> This program was implemented in C language and SQLite database. In the database to relate tables of cameras and accessories was used a third table with relation of the type many-to-many. In some cases the TRANSACT function is used to register a new accessory relating to the model of the camera.

	To delete a camera and delete the accessories, we use cascading delete. Basically all delete, insert, select logic were executed in SQL (Structured Query Language) from the SQLite database.


## Bulding and execute program:

#### Tested em macOS and Linux Debian 9 64 bits

Open terminal end enter in project directory execute Makefile:

$make clean
$make all

#### Running program in folder "Release":

$cd Release/
$ ./PhotoShop.o

### Using...

######!!!!!!!!!!!!!!!!!!!!!!!!  CREATE DATABASE IN FIRST TIME !!!!!!!!!!!!!!!!!!!!!!!

#####	Create a new database when using the program for the first time or to delete and re-create a new. Use option 10 to create a new database.


##### PRINCIPAL MENU:


######################################################################

	Xcompany Assessoria em Sistemas de Informação            
	Welcome to Photographic Equipament Store!               

######################################################################
####	Select a option and press [ENTER]:
----------------------------------------------------------------------
	[ 1 ] Add new camera
	[ 2 ] Add new accessories
	[ 3 ] Consult all cameras
	[ 4 ] Consult all accessories
	[ 5 ] Consult camera using model, returning accessories order
	by type and price
	[ 6 ] Remove camera using model
	[ 7 ] Remove accessory using id
	[ 8 ] Update Camera list using model
	[ 9 ] Update Accessories using id
	[ 10 ] Create new database (careful this erases the database and
	creates a new empty)
	[ 11 ] Quit
---------------------------------------------------------------------
	Type Option:

#### Registering a new camera


	######################################################################

	Xcompany Assessoria em Sistemas de Informação            
	Welcome to Photographic Equipament Store!               

######################################################################
#### Select a option and press [ENTER]:
----------------------------------------------------------------------
	[ 1 ] Add new camera
	[ 2 ] Add new accessories
	[ 3 ] Consult all cameras
	[ 4 ] Consult all accessories
	[ 5 ] Consult camera using model, returning accessories order
	by type and price
	[ 6 ] Remove camera using model
	[ 7 ] Remove accessory using id
	[ 8 ] Update Camera list using model
	[ 9 ] Update Accessories using id
	[ 10 ] Create new database (careful this erases the database and
	creates a new empty)
	[ 11 ] Quit
---------------------------------------------------------------------
	Type Option: 1

	############## Registering a new camera ##############

	Model: m7

	Manufacturer: LeicaS

	Weight in grams: 460

	Price: 25000.00

	Resolution in megapixel: 20

	Wifi type y or n to Yes or Not:y
