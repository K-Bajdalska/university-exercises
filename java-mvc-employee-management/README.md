# Employee Records Management System (Java MVC)

University project implementing an employee records management application in Java.

The application allows storing, browsing, adding, removing, saving, and restoring employee data through a console interface. The project was developed according to object-oriented programming principles and the MVC (Model–View–Controller) architectural pattern.

## Project Overview

The system manages two types of employees:

* Director
* Sales Representative

Each employee is identified by a unique PESEL number and contains a set of common and role-specific attributes.

### Director

* PESEL
* First name
* Last name
* Position
* Salary
* Business phone number
* Service allowance
* Service card number
* Monthly expense limit

### Sales Representative

* PESEL
* First name
* Last name
* Position
* Salary
* Business phone number
* Commission percentage
* Monthly commission limit

## Implemented Features

* Display employee list
* Add new employees
* Remove employees
* Employee search by PESEL
* PESEL uniqueness validation
* PESEL checksum verification
* Input validation
* Data serialization
* Backup and restore from file
* Console navigation system

## Technologies and Concepts

* Java
* Object-Oriented Programming (OOP)
* MVC Architecture
* Inheritance
* Polymorphism
* Encapsulation
* Abstract Data Types (ADT)
* Generic Collections
* Exception Handling
* File I/O
* Serialization

## Architecture

The application follows the MVC design pattern:

### Model

Responsible for business logic and data management.

Examples:

* Pracownik (abstract class)
* Dyrektor
* Handlowiec
* ListaPracownikow
* Pesel
* Walidator
* KopiaZapasowa

### View

Responsible for user interaction and console output.

Examples:

* Widok

### Controller

Coordinates communication between Model and View.

Examples:

* Kontroler

## Data Storage

Employees are stored in a generic collection based on `LinkedHashMap<String, Pracownik>` where:

* key = PESEL
* value = Employee object

This approach provides efficient employee lookup by PESEL identifier.

## Validation

The application validates:

* PESEL checksum
* PESEL uniqueness
* Numeric values
* Phone numbers
* Service card numbers
* Employee personal data

Invalid input is handled through exception-based validation mechanisms.

## Learning Outcomes

This project demonstrates practical use of:

* MVC architecture
* Abstract classes and inheritance
* Polymorphism
* Collection Framework
* Data validation
* Exception handling
* Serialization
* Separation of concerns

## Author

University coursework project created as part of Java Programming laboratories.
