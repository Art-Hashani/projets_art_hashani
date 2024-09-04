import java.util.ArrayList;

public class Bibliotheque {
    ArrayList<Document> listeD;
    ArrayList<Materiel> listeM;
    ArrayList<Adherant> listeA;
    public Bibliotheque() {
        listeD = new ArrayList<>(); // Initialisez listeD dans le constructeur
        listeM = new ArrayList<>();
        listeA = new ArrayList<>();
    }
    public void ajouterDocument(Document doc){
        listeD.add(doc);
    }
    public void ajouterMateriel(Materiel M){
        listeM.add(M);
    }
    public void ajouterAdherant(Adherant Adhe){
        listeA.add(Adhe);
    }
    
}
