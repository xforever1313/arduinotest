
Command ProcessCommand(const char* str, int strLen)
{
  String s(str);
  if (strLen == 0)
  {
    return Empty;
  }
  else if (s.equalsIgnoreCase("vers") || s.equalsIgnoreCase("version"))
  {
    return Version;
  }
  
  return SyntaxError;
}

