// Copyright (c) 2005, 2006 Fernando Luis Cacciola Carballal. All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
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
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_SURFACE_MESH_SIMPLIFICATION_EDGE_COLLAPSE_H
#define CGAL_SURFACE_MESH_SIMPLIFICATION_EDGE_COLLAPSE_H 1

#include <CGAL/boost/graph/properties.h>
#include <CGAL/boost/graph/named_function_params.h>

#include <CGAL/Surface_mesh_simplification/Detail/Edge_collapse.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/LindstromTurk.h>

CGAL_BEGIN_NAMESPACE

namespace Surface_mesh_simplification
{

template<class ECM
        ,class ShouldStop
        ,class VertexIndexMap
        ,class EdgeIndexMap
        ,class EdgeIsBorderMap
        ,class GetCost
        ,class GetPlacement
        ,class Visitor
        >
int edge_collapse ( ECM&                    aSurface
                  , ShouldStop       const& aShould_stop
                  
                  // optional mesh information policies 
                  , VertexIndexMap   const& aVertex_index_map     // defaults to get(vertex_index,aSurface) 
                  , EdgeIndexMap     const& aEdge_index_map       // defaults to get(edge_index,aSurface) 
                  , EdgeIsBorderMap  const& aEdge_is_border_map   // defaults to get(edge_is_border,aSurface) 
                  
                  // optional strategy policies - defaults to LindstomTurk
                  , GetCost          const& aGet_cost 
                  , GetPlacement     const& aGet_placement
                  
                  , Visitor*                aVisitor // Can be NULL
                  ) 
{
  typedef EdgeCollapse< ECM
                      , ShouldStop
                      , VertexIndexMap
                      , EdgeIndexMap
                      , EdgeIsBorderMap
                      , GetCost
                      , GetPlacement
                      , Visitor
                      >
                      Algorithm 
                      ;
                      
  Algorithm algorithm( aSurface
                     , aShould_stop
                     , aVertex_index_map
                     , aEdge_index_map
                     , aEdge_is_border_map
                     , aGet_cost
                     , aGet_placement
                     , aVisitor
                     ) ;
                     
  return algorithm.run();
}                          


struct Dummy_visitor
{
  template<class ECM>
  void OnStarted( ECM& ) {} 
  
  template<class ECM>
  void OnFinished ( ECM& ) {} 
  
  template<class ECM>
  void OnStopConditionReached( ECM& ) {} 
  
  template<class Edge, class ECM>
  void OnCollected( Edge const&, ECM& ) {}                
  
  template<class Edge, class ECM, class OFT, class Size_type>
  void OnSelected( Edge const&, ECM&, OFT const&, Size_type, Size_type ) {}                
  
  template<class Edge, class ECM, class OPoint>
  void OnCollapsing(Edge const&, ECM&, OPoint const& ) {}                
  
  template<class Edge, class ECM>
  void OnNonCollapsable(Edge const&, ECM& ) {}                
} ;

template<class ECM, class ShouldStop, class P, class T, class R>
int edge_collapse ( ECM& aSurface
                  , ShouldStop const& aShould_stop
                  , cgal_bgl_named_params<P,T,R> const& aParams 
                  ) 
{
  using boost::choose_param ;
  using boost::choose_const_pmap ;
  using boost::get_param ;
  
  LindstromTurk_params lPolicyParams ;
  
  boost::graph_visitor_t vis = boost::graph_visitor_t() ;
    
  return edge_collapse(aSurface
                      ,aShould_stop
                      ,choose_const_pmap(get_param(aParams,boost::vertex_index),aSurface,boost::vertex_index)
                      ,choose_const_pmap(get_param(aParams,boost::edge_index),aSurface,boost::edge_index)
                      ,choose_const_pmap(get_param(aParams,edge_is_border),aSurface,edge_is_border)
                      ,choose_param     (get_param(aParams,get_cost_policy), LindstromTurk_cost<ECM>())
                      ,choose_param     (get_param(aParams,get_placement_policy), LindstromTurk_placement<ECM>())
                      ,choose_param     (get_param(aParams,vis), ((Dummy_visitor*)0))
                      ) ;

}

template<class ECM, class ShouldStop>
int edge_collapse ( ECM& aSurface, ShouldStop const& aShould_stop ) 
{
  return edge_collapse(aSurface,aShould_stop, edge_index_map(get(boost::edge_index,aSurface)));
}

} // namespace Surface_mesh_simplification

CGAL_END_NAMESPACE

#endif // CGAL_SURFACE_MESH_SIMPLIFICATION_EDGE_COLLAPSE_H //
// EOF //
 
