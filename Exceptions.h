//
// Created by Alis Daniel on 19/06/2021.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "Auxiliaries.h"
#include <exception>

namespace mtm {
    class Exception;
    class GameException;

    class IllegalArgument;
    class IllegalCell;
    class CellEmpty;
    class MoveTooFar;
    class CellOccupied;
    class OutOfRange;
    class OutOfAmmo;
    class IllegalTarget;
}

class mtm::Exception : public std::exception {
protected:
    std::string error;
    Exception(std::string message):
            error(message)
    {}

public:
    virtual const char *what() const noexcept override{
        return error.c_str();
    }
};

class mtm::GameException : public mtm::Exception {
protected:
    std::string error;
    GameException(std::string message):
            Exception(message),
            error(message)
    {}
};

class mtm::IllegalArgument : public mtm::GameException {
public:
    IllegalArgument():
            GameException("A game related error has occurred: IllegalArgument")
    {}
};


class mtm::IllegalCell : public mtm::GameException {
public:
    IllegalCell():
            GameException("A game related error has occurred: IllegalCell")
    {}
};


class mtm::CellEmpty : public  mtm::GameException {
public:
    CellEmpty():
            GameException("A game related error has occurred: CellEmpty")
    {}
};


class mtm::MoveTooFar : public  mtm::GameException {
public:
    MoveTooFar():
            GameException("A game related error has occurred: MoveTooFar")
    {}
};


class mtm::CellOccupied : public  mtm::GameException {
public:
    CellOccupied():
            GameException("A game related error has occurred: CellOccupied")
    {}
};


class mtm::OutOfRange : public  mtm::GameException {
public:
    OutOfRange():
            GameException("A game related error has occurred: OutOfRange")
    {}
};

class mtm::OutOfAmmo : public  mtm::GameException {
public:
    OutOfAmmo():
            GameException("A game related error has occurred: OutOfAmmo")
    {}
};

class mtm::IllegalTarget : public  mtm::GameException {
public:
    IllegalTarget():
            GameException("A game related error has occurred: IllegalTarget")
    {}
};

#endif //EXCEPTIONS_H
