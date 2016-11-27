#include "shared_ptr.hpp"
#include <catch.hpp>
#include <iostream>

 
SCENARIO("count and get for empty shared", "[count&get]"){
 shared_ptr<size_t> s;
  REQUIRE(s.refs()==0);
 REQUIRE(s.get()==nullptr);
}

SCENARIO("get for shared initialize", "[getInShared]"){
 shared_ptr<size_t> s(new size_t[10]);
 REQUIRE(s.get()!=nullptr);
}

SCENARIO("Initialize Shared", "[InShGet]") {
	size_t * ptr = new size_t[10];
	shared_ptr<size_t> s(ptr);
	REQUIRE(ptr == s.get());
}

SCENARIO("Checking count", "[CheckCount]") {
	size_t * ptr = new size_t[10];
	shared_ptr<size_t> f_sp(ptr);

	REQUIRE(f_sp.refs() == 1);

	shared_ptr<size_t> s_sp(f_sp);

	REQUIRE(f_sp.refs() == 2);
	REQUIRE(s_sp.refs() == 2);

	shared_ptr<size_t> t_sp(s_sp);

	REQUIRE(f_sp.refs() == 3);
	REQUIRE(s_sp.refs() == 3);
	REQUIRE(t_sp.refs() == 3);
}
SCENARIO("My","[MY]"){

shared_ptr<size_t> s;
shared_ptr<size_t> s2(s);
REQUIRE(s2.refs()==0);
}


