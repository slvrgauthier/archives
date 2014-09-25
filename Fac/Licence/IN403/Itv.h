class Itv{
  public:
    float bi;
    float bs;

    Itv();
    Itv(float,float);

    float getBi();
    void setBi(float);
    float getBs();
    void setBs(float);

    void saisie();
    void afficher();
    bool appartient(float);
    float longueur();
    bool egal(Itv);
    bool inclu(Itv);
    bool disjoint(Itv);
    bool accole(Itv);
    bool imbrique(Itv);
    void translate(float);
};

void translate(Itv&,float);
