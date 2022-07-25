#pragma once

#include <vector>

#include "edge.hpp"
#include "graph_type.hpp"
#include "vertex.hpp"
#include "view_form.hpp"


namespace coursework {


template <typename T>
class BaseGraph
{
public: // definitions
    using data_t   = T;
    using edge_t   = Edge<data_t>;
    using vertex_t = Vertex<data_t>;
    using Vertices = std::vector<vertex_t>;
    using Edges    = std::vector<edge_t>;

protected: // fields
    int _k;
    Vertices _vertices;
    ViewForm _view_form;

public: // (de)ctors
    BaseGraph() = default;

    BaseGraph(Vertices&& vertices, GraphType type, ViewForm form)
    {
        //
    }

    BaseGraph(
        Vertices&& vertices,
        Edges&& edges,
        GraphType type,
        ViewForm form
    ) : BaseGraph(std::move(vertices), type, form)
    {
        //
    }

    ~BaseGraph() = default;

public: // user methods
    void
    directed()
    {
        // todo…
    }

    ViewForm
    dense() const
    { return _view_form; }

    edge_t*
    getEdge(const vertex_t& v1, const vertex_t& v2)
    {
        // todo…
    }

    void
    toListGraph()
    {
        // todo…
    }

    void
    toMatrixGrapg()
    {
        // todo…
    }

    void
    insertV()
    {
        // todo…
    }

    void
    deleteV()
    {
        // todo…
    }

    void
    insertE()
    {
        // todo…
    }

    void
    deleteE()
    {
        // todo…
    }
};


}

