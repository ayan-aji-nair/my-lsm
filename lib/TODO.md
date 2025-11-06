# To-Do

## 1. Basic SSTable flush
  if active_ has bytes > limit, then move to the sstable

  create a new wal file after writing to ss table from the immutable memtable

  how to move from active_ to imm_? when?

## 2. add one helper to return wal file paths for writer and reader. do this when log rotation happens

## 3. Checksums / SSTable headers
