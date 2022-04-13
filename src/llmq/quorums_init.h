// Copyright (c) 2018 The Dash Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef VECO_QUORUMS_INIT_H
#define VECO_QUORUMS_INIT_H

class CEvoDB;

namespace llmq
{

void InitLLMQSystem(CEvoDB& evoDb);
void DestroyLLMQSystem();

}

#endif //VECO_QUORUMS_INIT_H
