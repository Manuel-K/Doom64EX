// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 1993-1997 Id Software, Inc.
// Copyright(C) 2007-2012 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
//-----------------------------------------------------------------------------

#ifndef __D_THINK__
#define __D_THINK__

//
// Experimental stuff.
// To compile this as "ANSI C with classes"
//  we will need to handle the various
//  action functions cleanly.
//
typedef void(*actionf_v)(void);
typedef void(*actionf_p1)(void*);
typedef void(*actionf_p2)(void*, void*);

union actionf_t {
    actionf_v   acv;
    actionf_p1  acp1;
    actionf_p2  acp2;

    actionf_t():
        acv(nullptr)
    {
    }

    actionf_t(decltype(nullptr)):
        acv(nullptr)
    {
    }

    actionf_t(actionf_v p):
        acv(p)
    {
    }

    template <class T>
    actionf_t(void (*p)(T)):
        acp1(reinterpret_cast<actionf_p1>(p))
    {
    }

    template <class T, class U>
    actionf_t(void (*p)(T, U)):
        acp2(reinterpret_cast<actionf_p2>(p))
    {
    }

    operator bool() const
    {
        return acv == nullptr;
    }

    bool operator!() const
    {
        return acv == nullptr;
    }

    void operator()() const
    {
        acv();
    }

    template <class T>
    void operator()(T a) const
    {
        acp1(reinterpret_cast<void *>(a));
    }

    template <class T, class U>
    void operator()(T a, U b) const
    {
        acp2(reinterpret_cast<void *>(a), reinterpret_cast<void*>(b));
    }
};





// Historically, "think_t" is yet another
//  function pointer to a routine to handle
//  an actor.
typedef actionf_t  think_t;


// Doubly linked list of actors.
struct thinker_t {
    thinker_t*   prev;
    thinker_t*   next;
    think_t      function;

};

#endif
