SendPacket(2, "action|dialog_return\ndialog_name|backpack_menu\nbuttonClicked|1")

netid = GetLocal().netID
SendPacket(2, "action|dialog_return\ndialog_name|popup\nnetID|"..netid.."|\nnetID|"..netid.."|\nbuttonClicked|trade\n\n")

SendPacket(2, "action|dialog_return\ndialog_name|trade_item\nitemID|7188|\ncount|1\n")

SendPacket(2, "action|trade_accept\nstatus|1\n")

SendPacket(2, "action|dialog_return\ndialog_name|trade_confirm\nbuttonClicked|accept\n\n")