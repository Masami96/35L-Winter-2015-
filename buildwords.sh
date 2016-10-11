#! /bin/bash

#grab all of the words (they begin with <td>)
grep "<td>" |

#delete the HTML tags
sed 's/<[^>]*>//g' |

#delete all words in parenthesis
sed 's/([^)]*)//g' |

#delete all unnecessary spaces, returns, and tabs
tr -d ' /r/t' |

#delete all the blank lines
sed '/^$/d' |

#remove every other line (1,3,5,7,etc.)
sed '1~2d' |

#convert the ` to '
sed 's/`/'"'"'/g' |

#convert all uppercase to lowercase
tr '[:upper:]' '[:lower:]' |

#remove all words taht do not consist only of hawaiian characters
sed '/[^p^k^m^n^w^l^h^a^e^i^o^u^'\'']/d' |

#sort and remove the doubles
sort -u
