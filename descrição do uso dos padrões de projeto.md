# Uso de Padrões de Projeto

## Singleton Facade

main() é a função que implementa esse padrão. Ela é um singleton, já que funções não possuem múltiplas instâncias, e
também é uma facade, já que ela é a única interface com o usuário. O objetivo é que só haja uma forma de interagir com o
sistema e que ela exponha uma interface simples e abstrata do sistema, sendo responsável por qualquer chamada interna
necessária.

## Factory Method

As classes Persistance, PersistanceFactory, UserPersistence e TradePersistance implementam esse padrão. A classe
PersistanceFactory é uma factory method, já que ela é responsável por criar instâncias de subclasses de Persistance.
A classe Persistance é uma classe genérica e UserPersistence e TradePersistance são concretas, implementado persistência
para um tipo de dado. O uso desse padrão permite que o código seja reutilizado entre as persistências usando uma única
interface.

## Adapter

A classe UserManager_UserReportAdapter implementa esse padrão. Ela é um adapter, já que ela é responsável por adaptar
UserManager para uso no UserReport. O objetivo é que UserReport possa usar UserManager sem precisar conhecer a
implementação de UserManager.

## Template Method

A classe UserReport implementa esse padrão. Ela deixa a implementação dos passos da geração do relatório para as
subclasses, permitindo que as classe geradoras de relatório tenha a mesma interface. As subclasses de UserReport são
UserReportCSV e UserReportHTML, que implementam a geração de relatório em CSV e HTML, respectivamente.

## Iterator

As classes UserIterator e TradeIterator implementam esse padrão. Elas são iteradoras de UserManager e TradeManager,
respectivamente. O objetivo é que seja possível iterar sobre os usuários e trades do sistema sem precisar conhecer a
implementação de UserManager e TradeManager. A implementação segue o padrão de iteradores da biblioteca padrão do
C++.

## Chain of Responsibility

As classes UserLoginHandler e UserPasswordHandler, ambas estendendo a classe UserHandler, implementam esse padrão. Elas
validam o login e a senha de um usuário, respectivamente, e são encadeadas para que a validação seja feita em ordem.
O objetivo é que seja possível adicionar novas validações sem precisar alterar o código de validação existente.

## Command

As classes FormattedInputCommand, FOrmattedOutputCommand e PrintOptionsCommand, todas estendendo a classe Command,
implementam esse padrão. Elas são comandos que podem ser executados pela main(). O objetivo é que se evite repetição
de código para entrada e saída. FormattedInputCommand e FormattedOutputCommand fazem entrada e saída formatada, fazendo
flushing também, e PrintOptionsCommand imprime opções a partir de strings.

## Memento

As classes UserManagerMemento implementa esse padrão. UserManager usa essa classe para salvar o estado do sistema e
restaurar o estado anterior. O objetivo é que seja possível desfazer ações do usuário.
