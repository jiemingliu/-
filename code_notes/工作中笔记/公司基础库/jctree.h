/******************************************************************************
* 文件名: jctree.h
* 描述: 多叉树
* Copyright(c)2014-2016 JCDZ Co.,Ltd.
*
* 修改记录:
* --------------------
* v1.0   2014/04/12 14:28:8, lys 创建文件
*
******************************************************************************/
#ifndef _JCTREE_H_
#define _JCTREE_H_

#include <vector>
#include "jcbase.h"

using namespace std;

/******************************************************************************
* 函数名:JCTreeNode
* 描述: 多叉树节点,类似JCDoubleLinkNode的使用方法,作衔接作用
*
* 输入:
* 输出:
* 返回值:
*
* 修改记录:
* --------------------
*    2014/04/16 15:7:18, lys 创建函数
*
******************************************************************************/
class DLL_EXPORT JCTreeNode
{
public:
	JCTreeNode();
	virtual ~JCTreeNode();

    /******************************************************************************
    * 函数名:JCTreeNode.Parent
    * 描述: 父节点指针
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:8:30, lys 创建函数
    *
    ******************************************************************************/
	JCTreeNode *Parent();

    /******************************************************************************
    * 函数名:JCTreeNode.FirstChild
    * 描述: 第一个子节点
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:8:49, lys 创建函数
    *
    ******************************************************************************/
	JCTreeNode *FirstChild();

    /******************************************************************************
    * 函数名:JCTreeNode.LastChild
    * 描述: 最后一个子节点
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:9:5, lys 创建函数
    *
    ******************************************************************************/
	JCTreeNode *LastChild();

    /******************************************************************************
    * 函数名:JCTreeNode.SpecPosChild
    * 描述: 指定序号子节点(从0开始),不存在的节点返回NULL
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:10:15, lys 创建函数
    *
    ******************************************************************************/
	JCTreeNode *SpecPosChild(unsigned int nPos);

    /******************************************************************************
    * 函数名:JCTreeNode.PrevSibling
    * 描述: 前一个兄弟节点,不存在兄弟节点时指向自己
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:10:56, lys 创建函数
    *
    ******************************************************************************/
	JCTreeNode *PrevSibling();

    /******************************************************************************
    * 函数名:JCTreeNode.NextSibling
    * 描述: 下一个兄弟节点,不存在兄弟节点时指向自己
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:13:37, lys 创建函数
    *
    ******************************************************************************/
	JCTreeNode *NextSibling();

    /******************************************************************************
    * 函数名:JCTreeNode.NodeType
    * 描述: 节点类型,可自定义
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:13:59, lys 创建函数
    *
    ******************************************************************************/
	unsigned int NodeType();

    /******************************************************************************
    * 函数名:JCTreeNode.SiblingIndex
    * 描述: 本节点在兄弟节点中的排序(从0开始)
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:14:22, lys 创建函数
    *
    ******************************************************************************/
	unsigned int SiblingIndex();

	/******************************************************************************
	* 函数名:JCTreeNode.SiblingIndexInLevel
	* 描述: 本节点在同一层次节点中的排序(从0开始)
	*
	* 输入:
	* 输出:
	* 返回值:
	*
	* 修改记录:
	* --------------------
	*    2014/05/08 23:21:41, lys 创建函数
	*
	******************************************************************************/
	unsigned int SiblingIndexInLevel();

    /******************************************************************************
    * 函数名:JCTreeNode.SetNodeType
    * 描述: 设置节点类型
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:17:5, lys 创建函数
    *
    ******************************************************************************/
	void SetNodeType(unsigned int nType);

    /******************************************************************************
    * 函数名:JCTreeNode.IsRoot
    * 描述: 是否根节点(无父节点)
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:17:35, lys 创建函数
    *
    ******************************************************************************/
	bool IsRoot();

    /******************************************************************************
    * 函数名:JCTreeNode.IsLeaf
    * 描述: 是否叶子节点(无子节点)
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:18:7, lys 创建函数
    *
    ******************************************************************************/
	bool IsLeaf();

    /******************************************************************************
    * 函数名:JCTreeNode.IsNoSibling
    * 描述: 是否无兄弟节点
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:18:32, lys 创建函数
    *
    ******************************************************************************/
	bool IsNoSibling();

    /******************************************************************************
    * 函数名:JCTreeNode.Depth
    * 描述: 节点在树种深度(由根节点从0开始递增)
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:18:55, lys 创建函数
    *
    ******************************************************************************/
	unsigned int Depth();

    /******************************************************************************
    * 函数名:JCTreeNode.ChildCount
    * 描述: 子节点个数
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:19:31, lys 创建函数
    *
    ******************************************************************************/
	unsigned int ChildCount();

    /******************************************************************************
    * 函数名:JCTreeNode.AddChild
    * 描述: 添加子节点
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:19:57, lys 创建函数
    *
    ******************************************************************************/
	void AddChild(JCTreeNode &tChild);

    /******************************************************************************
    * 函数名:JCTreeNode.ClearChild
    * 描述: 清除子节点
    *
    * 输入:
    * 输出:
    * 返回值:
    *
    * 修改记录:
    * --------------------
    *    2014/04/16 15:19:57, lys 创建函数
    *
    ******************************************************************************/
	void ClearChild();

protected:
	JCTreeNode *m_pParent;
	JCTreeNode *m_pPrevSibling, *m_pNextSibling;
	vector<JCTreeNode *> m_tPchild;
	unsigned int m_nNodeType;

	void _InitSibling(JCTreeNode *pNode);
	void _InitChild(JCTreeNode *pNode);
	void _AddSibling(JCTreeNode *pNew, JCTreeNode *pPrev, JCTreeNode *pNext);
	void _BreakSibling(JCTreeNode *pPrev, JCTreeNode *pNext);
	void _LinkToSiblingTail(JCTreeNode &tHeadSibling);
};

#endif /* _JCTREE_H_ */

