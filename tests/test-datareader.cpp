#include "../DataReader.h"
#include "catch.hpp"

#include <iostream>
#include <string>

DataReader dataReader = DataReader("data/bgg_db_1806.csv");
DataReader dataReader2 = DataReader("data/bgg_db_1806.csv", 500);

TEST_CASE("DataReader::size #1", "[part=1][valgrind]") {

    REQUIRE(dataReader.size() == 4999);
}

TEST_CASE("DataReader::size #2", "[part=1][valgrind]") {

    REQUIRE(dataReader2.size() == 500);
}

TEST_CASE("DataReader::getObject #1", "[part=1][valgrind]") {
    
    DataObject obj = dataReader2.getObject("The Castles of Burgundy");

    REQUIRE(obj.rank == 12);
    REQUIRE(obj.avg_time == 90);
    REQUIRE(obj.avg_rating == 8.12383);
}

TEST_CASE("DataReader::getObject #2", "[part=1][valgrind]") {
    
    DataObject obj = dataReader2.getObject(12);

    REQUIRE(obj.name == "7 Wonders Duel");
    REQUIRE(obj.rank == 13);
    REQUIRE(obj.avg_time == 30);
    REQUIRE(obj.avg_rating == 8.14559);
}

TEST_CASE("DataReader::getObject #3", "[part=1][valgrind]") {
    
    DataObject obj = dataReader2.getObject(501);

    REQUIRE(obj.rank == -1);
}

TEST_CASE("DataReader::getObject #4", "[part=1][valgrind]") {
    
    DataObject obj = dataReader2.getObject("Magic Realm");

    REQUIRE(obj.rank == -1);
}

TEST_CASE("DataReader::operator[] #1", "[part=1]") {

    DataObject obj = dataReader2[18];

    REQUIRE(obj.name == "Viticulture Essential Edition");
    REQUIRE(obj.rank == 19);
    REQUIRE(obj.avg_time == 90);
    REQUIRE(obj.avg_rating == 8.17385);
}

TEST_CASE("DataReader::operator[] #2", "[part=1][valgrind]") {

    DataObject obj = dataReader2["A Feast for Odin"];

    REQUIRE(obj.rank == 30);
    REQUIRE(obj.avg_time == 120);
    REQUIRE(obj.avg_rating == 8.18983);
}

TEST_CASE("DataReader::operator[] #3", "[part=1][valgrind]") {

    DataObject obj = dataReader2["Magic Realm"];

    REQUIRE(obj.rank == -1);
}

TEST_CASE("DataReader::operator[] #4", "[part=1][valgrind]") {

    DataObject obj = dataReader2[550];

    REQUIRE(obj.rank == -1);
}

TEST_CASE("DataReader::getObjectIndex", "[part=1][valgrind]") {

    REQUIRE(dataReader2.getObjectIndex("7 Wonders") == 41);
    REQUIRE(dataReader2.getObjectIndex("El Grande") == 55);
    REQUIRE(dataReader2.getObjectIndex("Merchants & Marauders") == 199);
    REQUIRE(dataReader2.getObjectIndex("Magic Realm") == -1);
}