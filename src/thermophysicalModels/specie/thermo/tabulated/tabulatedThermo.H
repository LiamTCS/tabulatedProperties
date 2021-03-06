/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2012 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::tabulatedThermo

Description
    Constant properties thermodynamics package
    templated into the equationOfState.

SourceFiles
    tabulatedThermoI.H
    tabulatedThermo.C

\*---------------------------------------------------------------------------*/

#ifndef tabulatedThermo_H
#define tabulatedThermo_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// Forward declaration of friend functions and operators

template<class EquationOfState> class tabulatedThermo;

template<class EquationOfState>
Ostream& operator<<
(
    Ostream&,
    const tabulatedThermo<EquationOfState>&
);


/*---------------------------------------------------------------------------*\
                           Class tabulatedThermo Declaration
\*---------------------------------------------------------------------------*/

template<class EquationOfState>
class tabulatedThermo
:
    public EquationOfState
{
    // Private data

        //- Interpolation table with specific heat
        interpolation2DTable<scalar> cpTable_;

        
    // Private Member Functions

        //- Construct from components
        //- Construct from components
        inline tabulatedThermo
        (
            const EquationOfState& st,
            const interpolation2DTable<scalar> cpTable,
            const interpolation2DTable<scalar> hTable
        );

public:

    // Public data

        //- Interpolation table with enthalpy
        interpolation2DTable<scalar> hTable;

        //- Construct from Istream
        tabulatedThermo(Istream&);

        //- Construct from dictionary
        tabulatedThermo(const dictionary& dict);

        //- Construct as named copy
        inline tabulatedThermo(const word&, const tabulatedThermo&);

        //- Construct and return a clone
        inline autoPtr<tabulatedThermo> clone() const;

        //- Selector from Istream
        inline static autoPtr<tabulatedThermo> New(Istream& is);

        //- Selector from dictionary
        inline static autoPtr<tabulatedThermo> New(const dictionary& dict);


    // Member Functions

        //- Return the instantiated type name
        static word typeName()
        {
            return "tabulated<" + EquationOfState::typeName() + '>';
        }

        //- Limit the temperature to be in the range Tlow_ to Thigh_
        inline scalar limit(const scalar T) const;


        // Fundamental properties

            //- Heat capacity at constant pressure [J/(kmol K)]
            inline scalar cp(const scalar p, const scalar T) const;

            //- Absolute Enthalpy [J/kmol]
            inline scalar ha(const scalar p, const scalar T) const;

            //- Sensible enthalpy [J/kmol]
            inline scalar hs(const scalar p, const scalar T) const;

            //- Chemical enthalpy [J/kmol]
            inline scalar hc() const;

            //- Entropy [J/(kmol K)]
            inline scalar s(const scalar p, const scalar T) const;


        // I-O

            //- Write to Ostream
            void write(Ostream& os) const;


    // IOstream Operators

        friend Ostream& operator<< <EquationOfState>
        (
            Ostream&,
            const tabulatedThermo&
        );
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include "tabulatedThermoI.H"

#ifdef NoRepository
#   include "tabulatedThermo.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
