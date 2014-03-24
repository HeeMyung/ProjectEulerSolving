#ifndef __HM_GRAPH_H_
#define __HM_GRAPH_H_

#include <set>
#include <vector>
#include <map>
namespace HeeM
{
	template<class Key, class Weight = int> class Graph
	{
	public:
		Graph()
		{
		}
		virtual ~Graph()
		{
		}

		struct EdgeInfo
		{
			Key to;
			Weight weight;
		};
		struct VertexInfo
		{
			Key key;
			std::vector<EdgeInfo*> edgeVector;
			std::map<Key, EdgeInfo*> edgeMap;
		};

		void AddVertex(const Key& key);
		void AddEdge(const Key& from, const Key& to, const Weight& weight);
		Weight GetWeight(const Key& from, const Key& to);
		
	private:
		std::vector<VertexInfo*> vertexVector;
		std::map<Key, VertexInfo*> vertexMap;
		bool directional;
	};


	template<class K, class W>
	void Graph<K,W>::AddVertex(const K& key)
	{
		VertexInfo* vinfo = new VertexInfo();
		vinfo->key = key;
		vinfo->edgeVector.clear();
		vinfo->edgeMap.clear();
		vertexVector.push_back(vinfo);
		vertexMap[key] = vinfo;
	}

	template<class K, class W>
	void Graph<K,W>::AddEdge(const K& from, const K& to, const W& weight)
	{
		if( vertexMap.find(from) == vertexMap.end() || vertexMap.find(to) == vertexMap.end() )
			// 해당하는 정점이 없음.. ㄷㄷ;
			return;
		VertexInfo *vFrom = vertexMap[from], *vTo = vertexMap[to];
		EdgeInfo* einfo = new EdgeInfo();
		einfo->to = to;
		einfo->weight = weight;
		vFrom->edgeVector.push_back(einfo);
		vFrom->edgeMap[to] = einfo;

		if( !directional )
		{
			einfo = new EdgeInfo();
			einfo->to = from;
			einfo->weight = weight;
			vTo->edgeVector.push_back(einfo);
			vTo->edgeMap[from] = einfo;
		}
	}

	template<class K, class W>
	W Graph<K,W>::GetWeight(const K& from, const K& to)
	{
		if( vertexMap.find(from) == vertexMap.end() || vertexMap.find(to) == vertexMap.end() )
			// 해당하는 정점이 없음.. ㄷㄷ;
			return W();
		VertexInfo *vFrom = vertexMap[from];
		if( vFrom->edgeMap.find(to) == vFrom->edgeMap.end() )
			return W();
		return vFrom->edgeMap[to]->weight;
	}
}


#endif
