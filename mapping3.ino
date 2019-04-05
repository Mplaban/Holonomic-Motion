struct node
{
  int x;
  int y;
  int value;
  struct node *next;
}*path, *present;

struct last
{
  int x;
  int y;
} l;

const int interuptxA = 2;
const int interuptxB = 4;
const int interuptyA = 3;
const int interuptyB = 5;
bool mat[10][10] = {0};
volatile int x = 0;
volatile int y = 0;
const int dist = 500;
int xAstate, xBstate, yAstate, yBstate;
int xdist = 0, ydist = 0;
int n=1;

int check_button()
{
  //code to check button press
  //0 for no button press
  //1 for button press
}

void Count_pulse_x () {
  xAstate = digitalRead(interuptxA);
  xBstate = digitalRead(interuptxB);
  if (xBstate == xAstate)
    x--;
  else if (xBstate != xAstate)
    x++;
  if (x >= dist)
  {
    xdist = xdist + 1;
    x = 0;
  }
  else if (x <= (-1 * dist))
  {
    xdist = xdist - 1;
    x = 0;
  }
}

void Count_pulse_y () {
  yAstate = digitalRead(interuptyA);
  yBstate = digitalRead(interuptyB);
  if (yBstate == yAstate)
    y--;
  else if (yBstate != yAstate)
    y++;
  if (y >= dist)
  {
    ydist = ydist + 1;
    y = 0;
  }
  else if (y <= (-1 * dist))
  {
    ydist = ydist - 1;
    y = 0;
  }
}

void print_path()
{
  int lastX = 0,lastY = 0;
  struct node *n = path;
  while (n != NULL)
  {
    if(n->x>lastX)
        Serial.print("\t");
    if(n->y>lastY)
        Serial.println();
    Serial.print(n->value);
    lastX=n->x;
    lastY=n->y;
    n = n->next;
  }
}

void create(int xpoint, int ypoint)
{
  if (xpoint != l.x || ypoint != l.y)
  {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->x = xpoint;
    p->y = ypoint;
    p->value = check_button();
    p->next = NULL;
    present->next = p;
    present = present->next;
    l.x = xpoint;
    l.y = ypoint;
  }
  
  print_path();
}

void setup() {
  Serial.begin(115200);
  pinMode(interuptxA, INPUT);
  digitalWrite(interuptxA, HIGH);
  pinMode(interuptxB, INPUT);
  digitalWrite(interuptxB, HIGH);
  pinMode(interuptyA, INPUT);
  digitalWrite(interuptyA, HIGH);
  pinMode(interuptyB, INPUT);
  digitalWrite(interuptyB, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  path = (struct node *)malloc(sizeof(struct node));
  path->x = 0;
  path->y = 0;
  path->value=1;
  path->next = NULL;
  present = path;
  l.x = 0;
  l.y = 0;
  attachInterrupt(digitalPinToInterrupt(interuptxA), Count_pulse_x, RISING);
  attachInterrupt(digitalPinToInterrupt(interuptyA), Count_pulse_y, RISING);
  Serial.println("Setup executed");
}

void loop() {
  digitalWrite(8, HIGH);
  /*Serial.print("pulse_count x:");
    Serial.print('\t');
    Serial.print(x);
    Serial.print("pulse_count y:");
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print("dist: ");
    Serial.print(xdist);
    Serial.print('\t');
    Serial.print(ydist);
    Serial.println();*/
  create(xdist, ydist);
}
