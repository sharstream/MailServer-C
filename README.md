# MailServer
c++ OOP

1. En este proyecto, “Servidores de Correos”, hemos descompuesto los objetivos  en los pasos:

•	Administrador Dominios y Servidores

•	Administrar Cuentas

•	Acceder una cuenta de en Servidor escogido y revisar el buzón

•	Trabajar y Revisar  los correos

•	Guardar y Cargar toda la información.

•	Reportes que se especifican en el enunciado

2. Estructura del  XML utilizado. Justificación

?xml version=\"1.0\"?
<Domains>
    <Servers>
       <Server>
           <NameDomain>Nombre Server 1</ NameDomain >
           <Tope de Cuenta>Top 1</ Tope de Cuenta >
           <Maximo de Tamaño del correo>Max 1</ Maximo de Tamaño del correo >

           <Accounts>
                 <Account>  //primera cuenta
                      <User> User 1  </ User >
                      <Password> Password 1</ Password >             
                      <Cuota> Cuota 1 </ Cuota >
                      <Adress> Adress 1  </ Adress >
                      <Persons> 
                         <Person>  Person 1  </ Person >
                             <Name> Name 1  </ Name >
                             <Apellidos> Apellidos 1  </ Apellidos >
                             <Age>Age 1 </ Age >    
                             <Sex> Sexo 1 </ Sex >
                             <Ocupation>Ocupacion 1</ Ocupation >
                       </ Person >
                  </Account>
                       .
                       .
                       .            
                       …
 
                  <Account>  //ultima cuenta
                        …
                  </Account>
                 </ Accounts >
          </ Server >
      </ Servers >
      </ Domains >
