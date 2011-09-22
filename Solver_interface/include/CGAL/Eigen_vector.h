// Copyright (c) 2011  INRIA Bordeaux Sud-Ouest (France), All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
// Author(s)     : Gael Guennebaud

#ifndef CGAL_EIGEN_VECTOR_H
#define CGAL_EIGEN_VECTOR_H

#include <CGAL/basic.h> // include basic.h before testing #defines

#include <Eigen/Core>

namespace CGAL {

/// The class Eigen_vector
/// is a C++ wrapper around Eigen' dense vector type Matrix<T,Dynamic,1>.
///
/// @heading Is Model for the Concepts: Model of the SparseLinearAlgebraTraits_d::Vector concept.

template<class T> 
class Eigen_vector : public Eigen::Matrix<T,Eigen::Dynamic,1>
{
// Public types
public:

   typedef T NT;
   typedef Eigen::Matrix<T,Eigen::Dynamic,1> EigenType;

// Public operations
public:

#ifndef CGAL_CFG_MATCHING_BUG_6
  using EigenType::operator=;
#else
  Eigen_vector<T>& operator=(const Eigen_vector<T>& other){
    return static_cast<EigenType&>(*this) = other.eigen_object();
  }
#endif


   /// Create a vector initialized with zeros.
   Eigen_vector(int dimension)
     : EigenType(dimension)
   {
     this->setZero();
   }

   /// Copy constructor.
   Eigen_vector(const Eigen_vector& toCopy)
     : EigenType(toCopy)
   {
   }

   ~Eigen_vector()
   {
   }

   /// Return the vector's number of coefficients.
   int dimension() const {
       return this->size();
   }

   /// Get TAUCS vector wrapped by this object.
   const EigenType& eigen_object() const {
       return *this;
   }
   EigenType& eigen_object() {
       return *this;
   }
   
   void set(int i,NT value) {
     this->operator[](i)=value;
   }
   
   NT* vector() {return this->data();}
   
};

} //namespace CGAL

#endif // CGAL_EIGEN_VECTOR_H
