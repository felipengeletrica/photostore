###This program is part of a challenge requested by the company DbServer 
###as part of the selective process for programming in C.
###	A schedule of camera registrations is implemented as well as its accesses 
###that must be linked to the corresponding machines.\

## Bulding and execute program: 

#### Tested em macOS and Linux Debian 9 64 bits

Open terminal end enter in project directory execute Makefile:

$make clean
$make all

#### Running program in folder "Release":

$cd Release/
$ ./PhotoShop.o


## The Challenge 

<p> Here's the challenge:

####In Portuguese:
####
####		Em nossa loja de acessórios fotográficos, queremos cadastrar câmeras e acessórios, com suas ####características e preços. 
####		Gostaríamos de pesquisar, adicionar e remover itens. 
####		Cada máquina possui as seguintes características: código identificador, modelo, marca, peso, ####preço, resolução e se tem Wi-fi ou não. Cada acessório possui as seguintes características: código ####identificador, ####tipo de acessório, marca, descrição e preço. Além disso, para cada acessório existe uma lista de câmeras com as ####quais ele é compatível. 
####		Os tipos de acessório são: lente, flash e tripé.
####		A pesquisa mais importante para nós é consultar uma câmera através de seu modelo e apresentar ####todas as suas características e uma lista de acessórios compatíveis, sendo esta ordenada pelo tipo ####de acessório e depois pelo 
####preço. A lista de acessórios compatíveis só precisa mostrar o tipo, a descrição e o preço de cada acessório.
####		Em segundo lugar, precisamos remover uma câmera pelo seu código identificador e atualizar as listas de câmeras compatíveis de cada acessório em razão dessa exclusão
####		Por fim, precisamos adicionar câmeras novas e acessórios novos, informando, neste último caso, com quais câmeras o novo acessório é compatível.
####		O programa deve ser desenvolvido em linguagem C. 
####	
####		Serão avaliados os seguintes itens:
####	
####		* Legibilidade e expressividade;
####		* Reusabilidade;
####		* Boas práticas e princípios de código limpo;
####		* Preferência pelo idioma inglês;
####		* Simplicidade;
####		* Escolha de estruturas de dados e tipos de dados.
####		Itens que não serão avaliados:
####		* Eficiência;
####		* Interface.


##  challenging... 

#### <t> This program was implemented in C language and SQLite database. In the database to relate tables of cameras and accessories was used a third table with relation of the type many-to-many. In some cases the TRANSACT function is used to register a new accessory relating to the model of the camera.
#### To delete a camera and delete the accessories, we use cascading delete. Basically all delete, insert, select logic were executed in SQL (Structured Query Language) from the SQLite database.



###!!!!!!!!!!!!!!!!!!!!!!!!  CREATE DATABASE IN FIRST TIME !!!!!!!!!!!!!!!!!!!!!!!

####	Create a new database when using the program for the first time or to delete and re-create a new. Use option 10 to create a new database. 


### PRINCIPAL MENU:


######################################################################

	DBServer Assessoria em Sistemas de Informação            
	Welcome to Photographic Equipament Store!               

######################################################################
<t>	Select a option and press [ENTER]:
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

	DBServer Assessoria em Sistemas de Informação            
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

	Manufacturer: Leica

	Weight in grams: 460

	Price: 25000.00

	Resolution in megapixel: 20

	Wifi type y or n to Yes or Not:y

	