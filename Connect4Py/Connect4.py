from Connect4Tools.BoardNode import BoardNode
from Connect4Tools.BoardTools import BoardTools


node = BoardNode(6,7)
bt = BoardTools()

print(bt.GetNextEmpyRow(node.boardState,0))

