    # MailServer
    c++ OOP

    Copyright (c) 2007 by 
    
    ALEJANDRO RUIZ COUTIN 
    
    DAVID PEREZ ALVAREZ

**Resumen**

En este proyecto  estamos desarrollando una aplicación que simula una situación por lo tanto la línea de la realidad, en el sentido de la funcionalidad, la flexibilidad para el desarrollo de los aspectos, actualizaciones y la creación  de un modelo real a partir de este, son tan  relativa como transparente. Partiendo de este punto tomamos las consideraciones de las políticas y libertades que restringen el intercambio de  los usuarios con este programa, para su interacción en tiempo real.


1. En este proyecto, “Servidores de Correos”, hemos descompuesto los objetivos  en los pasos:

•	Administrador Dominios y Servidores

•	Administrar Cuentas

•	Acceder una cuenta de en Servidor escogido y revisar el buzón

•	Trabajar y Revisar  los correos

•	Guardar y Cargar toda la información.

•	Reportes que se especifican en el enunciado

2.Estructura del  XML utilizado. Justificación


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